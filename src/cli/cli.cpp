#include "cli/cli.h"
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/WithColor.h>

using namespace llvm;

// Group options into a category
static llvm::cl::OptionCategory IRSymbolizerCategory("IRSymbolizer Options");

// Modes (booleans)
cl::opt<bool> SampleFlag("sample",       cl::desc("Sample the binary with default frequency"), llvm::cl::cat(IRSymbolizerCategory));
cl::opt<bool> Addr2LineFlag("addr2line", cl::desc("Map address(es) to source line"),           llvm::cl::cat(IRSymbolizerCategory));
cl::opt<bool> Addr2IRFlag("addr2ir",     cl::desc("Map address(es) to LLVM IR"),               llvm::cl::cat(IRSymbolizerCategory));

// Parameters
cl::opt<std::string> BinPath("bin",   cl::desc("Input binary"),            cl::value_desc("filename"),    llvm::cl::cat(IRSymbolizerCategory));
cl::opt<std::string> Address("addr", cl::desc("Input address"),           cl::value_desc("hex address"), llvm::cl::cat(IRSymbolizerCategory));
cl::opt<unsigned>    Freq("freq",    cl::desc("Sampling frequency (Hz)"), cl::init(200),                 llvm::cl::cat(IRSymbolizerCategory));

// Outputs
cl::opt<std::string> OutputAddr2Line("output-addr2line", cl::desc("Output addr2line results in csv or txt"), cl::value_desc("format:name"), llvm::cl::cat(IRSymbolizerCategory));
cl::opt<std::string> OutputAddr2IR("output-addr2ir",     cl::desc("Output addr2ir results in csv or txt"),   cl::value_desc("format:name"), llvm::cl::cat(IRSymbolizerCategory));
cl::opt<std::string> OutputSamples("output-samples",     cl::desc("Output sampling results in csv or txt"),  cl::value_desc("format:name"), llvm::cl::cat(IRSymbolizerCategory));

bool parseAndValidateCommandLine(int argc, char **argv) {
  // Hide the LLVM default arguments from the --help
  llvm::cl::HideUnrelatedOptions(IRSymbolizerCategory);
  cl::ParseCommandLineOptions(argc, argv,
			      "IRSymbolizer\n"
			      "A CLI tool for sampling and mapping addresses to source or IR\n\n"
			      "Examples:\n"
			      "  IRSymbolizer --bin bin\n"
			      "  IRSymbolizer --addr2line --bin ./binfile --addr 0xaddress\n"
			      "  IRSymbolizer --addr2ir --bin ./binfile --addr 0xaddress\n"
			      "  IRSymbolizer --sample --bin ./binfile --freq 1000\n"
			      );

  if (argc == 1) {
    cl::PrintHelpMessage();
    return false;
  }

  if ((OutputAddr2Line.getNumOccurrences() && Addr2Line) ||
      (OutputAddr2IR.getNumOccurrences() && Addr2IR) ||
      (OutputSamples.getNumOccurrences() && Sample)) {
    WithColor::error() << "Output flag cannot be used with the respective active command.\n";
    cl::PrintHelpMessage();
    return false;
  }

  if ((Addr2Line || Addr2IR) && (Bin.empty() || (Addr.empty() && SampleAddrFile.empty()))) {
    WithColor::error() << "--addr2line or --addr2ir requires --bin and --addr.\n";
    cl::PrintHelpMessage();
    return false;
  }

  if (Sample && Bin.empty()) {
    WithColor::error() << "--sample requires --bin argument.\n";
    cl::PrintHelpMessage();
    return false;
  }

  return true;
}
