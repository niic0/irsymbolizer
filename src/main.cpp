#include "llvm/Support/InitLLVM.h" // InitLLVM
#include "llvm/Support/raw_ostream.h" // llvm::outs

#include "cli/cli.h"
#include "addr2ir/addr2ir.h"

int main(int argc, char* argv[]) {
  llvm::InitLLVM X(argc, argv);
  if(parseAndValidateCommandLine(argc, argv) == false)
    return 1;
  
  // CLI logic handler
  if (Sample) { // TODO
    std::cout << "Sampling binary: " << Binary << " at " << Frequency << " Hz\n";
    if (!OutputSamples.empty()) {
      // TODO
      std::cout << "Saving samples to: " << OutputSamples << "\n";
    }
  }

  if (Addr2IR) {
    // TODO
    std::cout << "Mapping address " << Address << " to IR for binary: " << Binary << "\n";
    if (!OutputIR.empty()) {
      // TODO
      std::cout << "Saving IR result to: " << OutputIR << "\n";
    }
  }

  if (Addr2Line) {
    std::cout << "Mapping address " << Address << " to source for binary: " << Binary << "\n";

    llvm::Expected<llvm::DILineInfo> lineInfoRes = symbolizeCodeWrapper(Module, PC_addr);
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
    if (!OutputLine.empty()) {
      std::cout << "Saving source result to: " << OutputLine << "\n";
    }
  }

  return 0;
}
