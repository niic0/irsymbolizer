#include "cli/cli.h"
#include <llvm/Support/CommandLine.h>
#include <llvm/Support/raw_ostream.h>
#include <llvm/Support/FileSystem.h>
#include <llvm/Support/WithColor.h>

using namespace llvm;

// Group options into a category
static llvm::cl::OptionCategory IRSymbolizerCategory("IRSymbolizer Options");

// Modes (booleans)
cl::opt<bool> SampleFlag("sample",         cl::desc("Sample the binary with default frequency"), llvm::cl::cat(IRSymbolizerCategory));
cl::opt<bool> Addr2LineFlag("addr2line",   cl::desc("Map address to source line"),               llvm::cl::cat(IRSymbolizerCategory));
cl::opt<bool> Addr2IRFlag("addr2ir",       cl::desc("Map address to LLVM IR"),                   llvm::cl::cat(IRSymbolizerCategory));
cl::opt<bool> Samples2IRFlag("samples2ir", cl::desc("Map addresses to LLVM IR"),                 llvm::cl::cat(IRSymbolizerCategory));

// Parameters
cl::opt<std::string> BinPath("bin",         cl::desc("Input binary"),                       cl::value_desc("filename"),    llvm::cl::cat(IRSymbolizerCategory));
cl::opt<std::string> IRLLVMPath("ir",       cl::desc("Input IR LLVM"),                      cl::value_desc("filename"),    llvm::cl::cat(IRSymbolizerCategory));
cl::opt<std::string> Address("addr",        cl::desc("Input address in Hexa"),              cl::value_desc("hex address"), llvm::cl::cat(IRSymbolizerCategory));
cl::opt<std::string> SamplesPath("samples", cl::desc("Sampling output (perf or internal)"), cl::value_desc("filename"),    llvm::cl::cat(IRSymbolizerCategory));
cl::opt<unsigned>    Freq("freq",           cl::desc("Sampling frequency (Hz)"),            cl::init(200),                 llvm::cl::cat(IRSymbolizerCategory));

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
			      "  IRSymbolizer --addr2ir --bin ./binfile --addr 0xaddress --ir output.ll\n"
			      "  IRSymbolizer --samples2ir --bin ./binfile --samples perf.data --ir output.ll\n"
			      "  IRSymbolizer --sample --bin ./binfile --freq 1000\n"
			      "  IRSymbolizer --addr2line --bin ./binfile --addr 0xaddress\n"
			      );

  // Binary needs at least one argument but it is more useful to output the specific missing field
  if (argc == 1) {
    cl::PrintHelpMessage();
    return false;
  }

  // Verify correct correspondance between mode and output asked
  if ((OutputAddr2Line.getNumOccurrences() && Addr2LineFlag) ||
      (OutputAddr2IR.getNumOccurrences() && Addr2IRFlag) ||
      (OutputSamples.getNumOccurrences() && SampleFlag)) {
    WithColor::error() << "Output flag cannot be used with the respective active command.\n";
    cl::PrintHelpMessage();
    return false;
  }

  // Verify that addr2line mode has correct arguments (e.g. bin and addr)
  if (Addr2LineFlag && (BinPath.empty() || Address.empty())) {
    WithColor::error() << "--addr2line requires --bin and --addr.\n";
    cl::PrintHelpMessage();
    return false;
  }

  // Verify that addr2ir mode has correct arguments (e.g. bin, addr and ir)
  if (Addr2IRFlag && (BinPath.empty() || Address.empty() || IRLLVMPath.empty())) {
    WithColor::error() << "--addr2ir requires --bin, --addr and --ir\n";
    cl::PrintHelpMessage();
    return false;
  }

  // Verify that samples2ir mode has correct arguments (e.g. bin, samples and ir)
  if (Samples2IRFlag && (BinPath.empty() || Address.empty() || IRLLVMPath.empty())) {
    WithColor::error() << "--addr2ir requires --bin, --addr and --ir\n";
    cl::PrintHelpMessage();
    return false;
  }

  // Verify that sample mode has correct argument (e.g. bin)
  if (SampleFlag && BinPath.empty()) {
    WithColor::error() << "--sample requires --bin argument.\n";
    cl::PrintHelpMessage();
    return false;
  }

  // Verify that the address is correctly set (e.g. is hexadecimal)
  uint64_t intAddr = 0;
  if (llvm::StringRef(Address).getAsInteger(0, intAddr)) {
    WithColor::error() << "Invalid hex address: " << Address << "\n";
    cl::PrintHelpMessage();
    return false;
  }

  return true;
}
