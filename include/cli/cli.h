// CommandLine.h
#pragma once

#include "llvm/Support/CommandLine.h"

extern llvm::cl::opt<bool> SampleFlag;
extern llvm::cl::opt<bool> Addr2LineFlag;
extern llvm::cl::opt<bool> Addr2IRFlag;
extern llvm::cl::opt<bool> Samples2IRFlag;
extern llvm::cl::opt<bool> TUIFlag;

extern llvm::cl::opt<std::string> BinPath;
extern llvm::cl::opt<std::string> IRPath;
extern llvm::cl::opt<std::string> SamplesPath;
extern llvm::cl::opt<std::string> Address;
extern llvm::cl::opt<unsigned> Freq;

extern llvm::cl::opt<std::string> OutputAddr2Line;
extern llvm::cl::opt<std::string> OutputAddr2IR;
extern llvm::cl::opt<std::string> OutputSamples;

bool parseAndValidateCommandLine(int argc, char **argv);
void printUsage();
