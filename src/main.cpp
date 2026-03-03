#include "llvm/Support/InitLLVM.h" // InitLLVM
#include "llvm/Support/raw_ostream.h" // llvm::outs

using namespace llvm;

int main(int argc, char* argv[]) {
  llvm::InitLLVM X(argc, argv);

  std::string Module = argv[1]; // Module = Binary, Shared Object or Archive
  uint64_t PC_addr = std::stoull(argv[2], nullptr, 16);  // Hex address

  DILineInfo lineInfo = symbolizeCodeWrapper(Module, PC_addr);

  if (lineInfo) {
    llvm::outs() << "Function: " << lineInfo->FunctionName << "\n";
    llvm::outs() << "File: " << lineInfo->FileName << ":" << lineInfo->Line << "\n";
  } else {
    llvm::errs() << "Failed to symbolize\n";
  }


  return 0;
}
