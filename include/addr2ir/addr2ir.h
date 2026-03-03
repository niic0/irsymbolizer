#pragma once

#include "llvm/DebugInfo/DIContext.h" // DILineInfo type

DILineInfo symbolyzeCodeWrapper(const std::string &ModuleName, uint64_t PC_addr);
