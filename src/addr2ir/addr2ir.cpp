#include "llvm/DebugInfo/DIContext.h" // DILineInfo type
#include "llvm/DebugInfo/Symbolize/Symbolize.h" // symbolizeCode function
#include "llvm/Object/ObjectFile.h" // SectionedAddress class type

using namespace llvm;

/* symbolizeCode is the addr2line function of llvm */
Expected<DILineInfo> symbolizeCodeWrapper(const std::string &ModuleName, uint64_t PC_addr) {
  DILineInfo LineInfo;
  symbolize::LLVMSymbolizer::Options opts;
  symbolize::LLVMSymbolizer symbolizer(opts);

  object::SectionedAddress addr {PC_addr, object::SectionedAddress::UndefSection};

  Expected<DILineInfo> lineInfo = symbolizer.symbolizeCode(ModuleName, addr);

  return lineInfo;
}



