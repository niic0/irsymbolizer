# Symbolize Code Test
This directory contains non regression tests for validating the correctness and robustness of the `SymbolizeCodeWrapper`. This test is here to report any problem across every version of the tool. This test is included in the CMake with the `ctest` utility. The csv contain the module (binary, archive or shared object), the address, the function, the file and the line. The test parse this file and take the module and the address as input and compare the output with the function, file and line present in the csv. At your own risk, you can add a line in the csv and paste the binary in the `input` directory to add a test. Of course, you will need to fill the needed data in the csv (e.g. address, function, file and line).

**csv example**
```csv
binary,addr,function,file,line,label
base_O0,0x401000,main,test.c,5,inlining
base_O2,0x402034,main,test.c,unrolling
base_O2,0x402069,main,test.c,shareobject
```

## Test Coverage

To better approach an industrial context, the binary comes from the Safran application Muscat. Each binary address are symbolized in the test..

NB: If not mentionned, modules are compiled with clang.

| Test Case      | Description                           | Purpose                                     |
|----------------|---------------------------------------|---------------------------------------------|
| `base_O0`      | C program compiled with `-O0 -g`      | Baseline case for addr-to-source accuracy   |
| `base_O2`      | Same source compiled with `-O2 -g`    | Tests inlining, unrolling, DWARF loss       |
| `base_O3`      | Same source compiled with `-O3 -g`    | Tests inlining, unrolling, DWARF loss       |
| `base_Ofast`   | Same source compiled with `-Ofast -g` | Tests inlining, unrolling, DWARF loss       |
| `stripped`     | Binary stripped of debug info         | Should fail gracefully                      |
| `shared_lib`   | Uses symbols from `.so`               | Validates DSO resolution                    |
| `static_lib`   | Uses `.a` symbols                     | Tests static symbol resolution              |
| `gcc_binary`   | Binary built with GCC                 | DWARF compatibility across compilers        |
| `icx_binary`   | Binary built with ICX                 | DWARF compatibility across compilers        |

## Usage

```bash
cd test/symbolizeCodeWrapper
./run_tests.sh       # Run symbolizer on test binaries and check output
```

## Expected Output Format

Each address should resolve to a correct source line and function name. Outputs are verified against `test_cases.csv`.

## Structure
```
tests/
├── input/         # Pre-built or generated test binaries
├── expected/      # Expected output
├── run_tests.sh   # The test process
└── README.md      # This documentation
```
