#pragma once

#include "llvm/DebugInfo/DIContext.h" // DILineInfo type

llvm::Expected<llvm::DILineInfo> symbolizeCodeWrapper(const std::string &ModuleName, uint64_t PC_addr);
