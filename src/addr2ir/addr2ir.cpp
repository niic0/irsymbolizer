#include "llvm/DebugInfo/DIContext.h" // DILineInfo type
#include "llvm/DebugInfo/Symbolize/Symbolize.h" // symbolizeCode function
#include "llvm/Object/ObjectFile.h" // SectionedAddress class type

// 1. Read PCs and organize them in a struct
//DONE      -> Custom struct or llvm ? llvm
//DONE      -> a) Read One address, reproduce what llvm-symbolizer do
//DONE            Workflow is: ./bin addr
//      -> b) Same with multiple address
//            Workflow is: ./bin addr_file

// 2. Map PCs address to source lines
//      -> Using llvm::DWARFContext, llvm::DWARFDie, ...
//      -> Goal is: 0x420 -> line 9 of file foo.cpp
//      -> Clarify the data structure in which each element will be stored

// 3a. Map source code correspondance to IR
//      -> Goal is: 0x420 --> line 9 of file foo.cpp --> IR BB

// 3b. Store informative data about compiler choices
//      -> Depend on the symbol encounter by the correlation (loops, variable, function)
//      -> Goal is: IR BB {unrolled, vectorized, etc...}

using namespace llvm;
using namespace addr2ir;

DILineInfo symbolizeCodeWrapper(const std::string &ModuleName, uint64_t PC_addr) {
  DILineInfo LineInfo;
  symbolize::LLVMSymbolizer::Options opts;
  symbolize::LLVMSymbolizer symbolizer(opts);

  object::SectionedAddress addr {PC_addr, object::SectionedAddress::UndefSection};

  Expected<DILineInfo> lineInfo = symbolizer.symbolizeCode(Module, addr);

  return lineInfo;
}
