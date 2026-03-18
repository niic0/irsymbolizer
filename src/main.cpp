#include "llvm/Support/InitLLVM.h" // InitLLVM
#include "llvm/Support/raw_ostream.h" // llvm::outs

#include "cli/cli.h"
#include "addr2ir/addr2ir.h"
#include "tui/tui.h"

int main(int argc, char* argv[]) {
  llvm::InitLLVM X(argc, argv);

  if(parseAndValidateCommandLine(argc, argv) == false)
    return 1;
  
  /* CLI logic handler */

  // Sampling mode
  if (SampleFlag) { // TODO
    llvm::outs() << "Sampling binary: " << BinPath << " at " << Freq << " Hz\n";
    if (!OutputSamples.empty()) {
      // TODO
      llvm::outs() << "Saving samples to: " << OutputSamples << "\n";
    }
  }

  if (Addr2IRFlag) { // Address to IR mode
    llvm::outs() << "Mapping address " << Address << " to IR for binary " << BinPath << " with the LLVM IR " << IRPath << "\n";

    // Hexa address to int address convert
    uint64_t intAddress = 0;
    llvm::StringRef(Address).getAsInteger(0, intAddress);

    // Build IR Instruction Context Index
    auto IRContextIndexOrErr = InstrIRContextIndex::buildIndex(IRPath);
    if (!IRContextIndexOrErr) {
      llvm::logAllUnhandledErrors(IRContextIndexOrErr.takeError(), llvm::errs(), "buildIndex error: ");
      return 1;
    }
    std::unique_ptr<InstrIRContextIndex> IRContextIndex = std::move(*IRContextIndexOrErr);

    // Get the IR Context of an address from IR Instruction Context Index
    auto InstrIRContextOrErr = addr2ir(BinPath, intAddress, *IRContextIndex);
    if (!InstrIRContextOrErr) {
      llvm::logAllUnhandledErrors(InstrIRContextOrErr.takeError(), llvm::errs(), "addr2ir error: ");
      return 1;
    }
    const InstrIRContextVec InstrIRContextVec = std::move(*InstrIRContextOrErr);

    // Address IR context print to standard Output
    prettyPrintInstrIRContext(InstrIRContextVec);

    // Address IR context file output
    if (!OutputAddr2IR.empty())
      llvm::outs() << "Saving IR result to: " << OutputAddr2IR << "\n";
  }

  // Samples to IR mode
  if (Samples2IRFlag) {
    llvm::outs() << "Mapping samples " << SamplesPath << " to IR for binary " << BinPath << " with the LLVM IR " <<  "\n";

    if (!OutputAddr2IR.empty()) {
      llvm::outs() << "Saving IR result to: " << OutputAddr2IR << "\n";
    }
  }

  // Address to line mode
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
      prettyPrintDILineInfo(lineInfo);
    } else {
      llvm::errs() << "Failed to symbolize\n";
    }

    // TODO
    if (!OutputAddr2Line.empty()) {
      llvm::outs() << "Saving source result to: " << OutputAddr2Line << "\n";
    }
  }

  // Text User Interface
  if(TUIFlag) {
    run_tui();
  }

  return 0;
}
