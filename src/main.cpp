#include "llvm/Support/InitLLVM.h" // InitLLVM
#include "llvm/Support/raw_ostream.h" // llvm::outs

#include "cli/cli.h"
#include "addr2ir/addr2ir.h"

int main(int argc, char* argv[]) {
  llvm::InitLLVM X(argc, argv);

  if(parseAndValidateCommandLine(argc, argv) == false)
    return 1;
  
  // CLI logic handler
  if (SampleFlag) { // TODO
    llvm::outs() << "Sampling binary: " << BinPath << " at " << Freq << " Hz\n";
    if (!OutputSamples.empty()) {
      // TODO
      llvm::outs() << "Saving samples to: " << OutputSamples << "\n";
    }
  }

  if (Addr2IRFlag) {
    // TODO
    llvm::outs() << "Mapping address " << Address << " to IR for binary: " << BinPath << "\n";
    if (!OutputAddr2IR.empty()) {
      // TODO
      llvm::outs() << "Saving IR result to: " << OutputAddr2IR << "\n";
    }
  }

  if (Addr2LineFlag) {
    llvm::outs() << "Mapping address " << Address << " to source for binary: " << BinPath << "\n";

    // Format the address in int
    uint64_t intAddress = 0;
    llvm::StringRef(Address).getAsInteger(0, intAddress);

    llvm::Expected<llvm::DILineInfo> lineInfoRes = symbolizeCodeWrapper(BinPath, intAddress);
    if (!lineInfoRes) {
      llvm::logAllUnhandledErrors(lineInfoRes.takeError(), llvm::errs(), "symbolize error: ");
      return 1;
    }
  
    llvm::DILineInfo lineInfo = *lineInfoRes; // Safe to use now

    if (lineInfo) {
      llvm::outs() << "Function: " << lineInfo.FunctionName << "\n";
      llvm::outs() << "File: " << lineInfo.FileName << ":" << lineInfo.Line << "\n";
    } else {
      llvm::errs() << "Failed to symbolize\n";
    }

    // TODO
    if (!OutputAddr2Line.empty()) {
      llvm::outs() << "Saving source result to: " << OutputAddr2Line << "\n";
    }
  }

  return 0;
}
