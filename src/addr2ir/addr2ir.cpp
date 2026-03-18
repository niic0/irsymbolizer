#include <string>

#include "llvm/AsmParser/Parser.h"
#include "llvm/DebugInfo/DIContext.h" // DILineInfo type
#include "llvm/DebugInfo/Symbolize/Symbolize.h" // symbolizeCode function
#include "llvm/IR/DebugInfoMetadata.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/Support/Error.h"
#include "llvm/Object/ObjectFile.h" // SectionedAddress class type
#include "llvm/Support/FormatVariadic.h"
#include "llvm/Support/Path.h" // sys::path::convert_to_slash function
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Support/WithColor.h"

#include "addr2ir/addr2ir.h"

using namespace llvm;

StringMap<uint32_t> FileToID;
uint32_t NextFileID = 0;

/* symbolizeCode is the addr2line function of llvm */
Expected<DILineInfo> symbolizeCodeWrapper(const std::string &ModuleName, uint64_t PC_addr) {
  DILineInfo LineInfo;
  symbolize::LLVMSymbolizer::Options opts;
  symbolize::LLVMSymbolizer symbolizer(opts);

  object::SectionedAddress addr {PC_addr, object::SectionedAddress::UndefSection};

  Expected<DILineInfo> lineInfo = symbolizer.symbolizeCode(ModuleName, addr);

  return lineInfo;
}

Expected<InstrIRContextVec> addr2ir(const std::string &ModuleName, uint64_t PC_addr, const InstrIRContextIndex &IRContextIndex) {
  // Get DWARF line info
  Expected<DILineInfo> LineInfo = symbolizeCodeWrapper(ModuleName, PC_addr);
  if (!LineInfo)
    return LineInfo.takeError();

  // Create the key
  uint32_t FilePathID = filePathToID(LineInfo->FileName);
  SourceLocKey Key{FilePathID, LineInfo->Line, LineInfo->Column};

  // Get the Map of Instructions vector in InstrIRContextIndex
  InstrIRContextMap Map = IRContextIndex.Map;

  // Find the InstrIRContext of a specific {file, line, col}
  InstrIRContextMap::const_iterator It = Map.find(Key);
  if (It == Map.end()) {
    std::string ErrMsg = "No IR context for location " + LineInfo->FileName + ":" +
                         std::to_string(LineInfo->Line) + ":" +
                         std::to_string(LineInfo->Column);
    return make_error<StringError>(ErrMsg, inconvertibleErrorCode());
  }

  return It->second;
}

Expected<std::unique_ptr<InstrIRContextIndex>> buildInstrIRContextIndex(const std::string &IRPath) {
  // Parse the IR and create variables
  auto OwnedContext = std::make_unique<LLVMContext>();
  SMDiagnostic Err;
  std::unique_ptr<llvm::Module> M = parseIRFile(IRPath, Err, *OwnedContext);

  if (!M) {
    std::string ErrStr;
    raw_string_ostream OS(ErrStr);
    Err.print("IRSymbolizer", OS);
    return make_error<StringError>("Module creation error when building the InstrContext index: " + ErrStr, inconvertibleErrorCode());
  }

  if(auto Err = M->materializeAll()) {
    return make_error<StringError>("Failed to materialize IR: " + toString(std::move(Err)), inconvertibleErrorCode());
  }

  auto Index = std::make_unique<InstrIRContextIndex>();
  Index->Context = std::move(OwnedContext);
  Index->Module = std::move(M);
  InstrIRContextMap &Map = Index->Map;

  // For each Instruction in each Basic Block in each Function
  for (Function &F : *Index->Module) {
    for (BasicBlock &BB : F) {
      for (Instruction &I : BB) {	
        DebugLoc DL = I.getDebugLoc();
	if (!DL)
	  continue;

	// Handles file name
	StringRef Filename = DL->getFilename();
	StringRef Directory = DL->getDirectory();
	SmallString<256> FullPath;
	if (!Filename.empty()) {
	  if (sys::path::is_absolute(Filename)) {
	    FullPath = Filename;
	  } else if (!Directory.empty()) {
	    FullPath = Directory;
	    sys::path::append(FullPath, Filename);
	  } else {
	    FullPath = Filename;
	  }
	} else if (!Directory.empty()) {
	  FullPath = Directory;
	} else {
	  return make_error<StringError>(
	      "Debug location is missing both directory and filename information.",
	      inconvertibleErrorCode());
	}

	// Fill data
	uint32_t FilePathID = filePathToID(FullPath);	
	unsigned Line = DL.getLine();
	unsigned Col  = DL.getCol();
	SourceLocKey Key = {FilePathID, Line, Col};

	InstrIRContext CurrentInstrIRContext = {
	  &I, &BB, &F, Filename.str(), Line, Col
	};

	InstrIRContextVec CurrentInstrIRContextVec = { CurrentInstrIRContext };
	auto Inserted = Map.insert(std::make_pair(Key, CurrentInstrIRContextVec));
	
	if (!Inserted.second) // key already exists
	  Inserted.first->second.push_back(CurrentInstrIRContext);
      }
    }
  }

  return std::move(Index);
}

uint32_t filePathToID(StringRef File) {
  // Normalized path format, agnostic of the OS
  std::string Normalized = sys::path::convert_to_slash(File); // llvm sys function
  auto It = FileToID.find(Normalized);

  if(It != FileToID.end())
    return It->second;

  const uint32_t AssignedID = NextFileID++;
  FileToID[Normalized] = AssignedID;
  return AssignedID;
}


// Print Handler

namespace { // Print helper
  constexpr unsigned LabelWidth = 16;
  void printSeparator(raw_ostream &OS) {
    OS << std::string(50, '=') << "\n";
  }
  StringRef getOrUnknown(StringRef Value) {
    return Value.empty() ? "<unknown>" : Value;
  }
  std::string formatLabel(StringRef Label, unsigned Indent = 2) {
    std::string Result(Indent, ' ');
    Result += Label.str();
    if (Result.size() < Indent + LabelWidth)
      Result.append(Indent + LabelWidth - Result.size(), ' ');
    return Result;
  }
}

void prettyPrintDILineInfo(const DILineInfo &LineInfo) {
  raw_ostream &OS = outs();
  printSeparator(OS);
  {
    WithColor Section(OS, raw_ostream::YELLOW, true);
    Section << "Symbolized Location\n";
  }
  if (!LineInfo) {
    WithColor Err(OS, raw_ostream::RED, true);
    Err << "  No debug line information available.\n";
    printSeparator(OS);
    return;
  }

  OS << formatLabel("Function") << " : "
     << getOrUnknown(LineInfo.FunctionName) << "\n";
  OS << formatLabel("File") << " : "
     << getOrUnknown(LineInfo.FileName) << "\n";

  std::string LineCol;
  if (LineInfo.Column)
    LineCol = formatv("{0}:{1}", LineInfo.Line, LineInfo.Column).str();
  else
    LineCol = formatv("{0}", LineInfo.Line).str();

  {
    WithColor Highlight(OS, raw_ostream::GREEN, true);
    Highlight << formatLabel("Line/Column") << " : " << LineCol << "\n";
  }
  printSeparator(OS);
}

void prettyPrintInstrIRContext(const InstrIRContextVec &Contexts) {
  raw_ostream &OS = outs();
  printSeparator(OS);
  {
    WithColor Title(OS, raw_ostream::CYAN, true);
    Title << formatv("IR Context Matches [{0}]\n", Contexts.size());
  }

  if (Contexts.empty()) {
    WithColor Warn(OS, raw_ostream::RED, true);
    Warn << "  No IR context recorded for this location.\n";
    printSeparator(OS);
    return;
  }

  for (size_t Index = 0; Index < Contexts.size(); ++Index) {
    const InstrIRContext &Ctx = Contexts[Index];
    {
      WithColor Entry(OS, raw_ostream::MAGENTA, true);
      Entry << formatv("  #{0}\n", Index + 1);
    }

    const Function *Func = Ctx.Func;
    const BasicBlock *BB = Ctx.BB;

    OS << formatLabel("Function", 4) << " : "
       << (Func ? Func->getName() : "<null>") << "\n";

    std::string BBLabel;
    if (!BB)
      BBLabel = "<null>";
    else if (BB->hasName())
      BBLabel = BB->getName().str();
    else
      BBLabel = "<anonymous>";
    OS << formatLabel("Basic Block", 4) << " : " << BBLabel << "\n";

    OS << formatLabel("Source", 4) << " : " << Ctx.Filename
       << ":" << Ctx.Line << ":" << Ctx.Col << "\n";

    {
      WithColor InstLabel(OS, raw_ostream::GREEN, true);
      InstLabel << "    Instruction\n";
    }
    OS << "      ";
    Ctx.Instr->print(OS);
    OS << "\n";
  }

  printSeparator(OS);
}
