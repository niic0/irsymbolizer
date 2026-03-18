#pragma once

#include <memory>
#include <string>
#include <vector>

#include "llvm/ADT/DenseMap.h"
#include "llvm/ADT/StringMap.h"
#include "llvm/DebugInfo/DIContext.h" // DILineInfo type
#include "llvm/IR/BasicBlock.h" // BasicBlock type
#include "llvm/IR/Function.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Instructions.h" // Instruction type
#include "llvm/Support/Error.h"
#include "llvm/Support/raw_ostream.h"

/* Forward Declarations */
struct InstrIRContext;
struct InstrIRContextIndex;
struct SourceLocKey;
struct SourceLocKeyInfo;
llvm::Expected<std::unique_ptr<InstrIRContextIndex>> buildInstrIRContextIndex(const std::string &IRPath);

/* namespace */
using InstrIRContextVec = std::vector<InstrIRContext>; // Vector of InstrContext
using InstrIRContextMap = llvm::DenseMap<SourceLocKey, InstrIRContextVec, SourceLocKeyInfo>; // Map of InstrContext based on file id, col and line

/* extern values */
extern llvm::StringMap<uint32_t> FileToID; // Map string to uint32_t, avoiding map with owernership handler
extern uint32_t NextFileID;

/* Structures */
struct InstrIRContext { // Context of each instruction
  llvm::Instruction *Instr; // Instruction
  llvm::BasicBlock  *BB;    // Basic Block
  llvm::Function    *Func;  // Fucntion

  std::string Filename;
  unsigned Line;
  unsigned Col;

  std::vector<std::string> InlineChain;

  std::string Opcode;
  std::vector<std::string> Operands;

  bool ConstantResult;

  uint64_t Address; // Address in DWARF section
};

struct InstrIRContextIndex { // Index of InstrContext, stay alive as long as Map is used
  std::unique_ptr<llvm::LLVMContext> Context; // LLVM IR context
  std::unique_ptr<llvm::Module> Module; // owns all Instruction/BBs
  InstrIRContextMap Map;

  static llvm::Expected<std::unique_ptr<InstrIRContextIndex>> buildIndex(const std::string &IRPath) {
    return buildInstrIRContextIndex(IRPath);
  }
};

struct SourceLocKey  { // Source Location in map
  uint32_t FilePathID;
  uint32_t Line;
  uint32_t Column;

  // Equality operator overload
  // Defines how two SourceLocKey objects are compared for equality
  bool operator==(const SourceLocKey &Other) const {
    return FilePathID == Other.FilePathID &&
           Line == Other.Line &&
           Column == Other.Column;
  }
};

struct SourceLocKeyInfo { // Structure for LLVM Map implementation
  static inline SourceLocKey getEmptyKey() {
    return {~0u, ~0u, ~0u};
  }
  static inline SourceLocKey getTombstoneKey() {
    return {~0u - 1, ~0u - 1, ~0u - 1};
  }
  static unsigned getHashValue(const SourceLocKey &K) {
    return llvm::hash_combine(K.FilePathID, K.Line, K.Column);
  }
  static bool isEqual(const SourceLocKey &A, const SourceLocKey &B) {
    return A == B;
  }
};

/* Functions */
llvm::Expected<llvm::DILineInfo> symbolizeCodeWrapper(const std::string &ModuleName, const uint64_t PC_addr);
llvm::Expected<InstrIRContextVec> addr2ir(const std::string &ModuleName, const uint64_t PC_addr, const InstrIRContextIndex &IRContextIndex);
uint32_t filePathToID(llvm::StringRef File);
void prettyPrintDILineInfo(const llvm::DILineInfo &LineInfo);
void prettyPrintInstrIRContext(const InstrIRContextVec &Contexts);
