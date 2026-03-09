# Symbolize Code Test
This directory contains non regression tests for validating the correctness and robustness of the `SymbolizeCodeWrapper`. This test is here to report any problem across every version of the tool. This test is run through CMake with the `ctest` utility. 

The csv is the input of the test. It contains the module (binary, archive or shared object), the address, the function, the file and the line. The test parse this file and take the module and the address as input and compare the output with the function, file and line present in the csv. You can add a line in the csv and paste the binary in the `input` directory to add a test. Of course, you will need to fill the needed data in the csv (e.g. address, function, file and line).

**csv example**
```csv
binary,addr,function,file,line,label
base_O0,0x401000,main,test.c,5,inlining
base_O2,0x402034,main,test.c,unrolling
base_O2,0x402069,main,test.c,shareobject
```

## Test Coverage

To better approach an industrial context, the binary comes from the Safran application Muscat.

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

## Note on how the dataset was obtain

### Finding inlined address

Get debug information about inlined decisions. Debug informations are display through the `objdump -g` command. Data are organized as bellow:

```bash
<depth><offset>: Abbrev Number: <num> (DW_TAG_inlined_subroutine)
```

Where:
- `<depth>`: Depth in the debug info hierarchy. E.g., `<4>` is deeper than `<3>`.
- `<offset>` : Byte offset into the `.debug_info` section for this DIE (Debug Info Entry).
- `<num>`: Index into the `.debug_abbrev` section telling how to decode this DIE.

For example:

```bash
$ objdump -g libMuscatNative.so | grep DW_TAG_inlined_subroutine

[...]
<9><a8678>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
<9><a8691>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
<10><a86a1>: Abbrev Number: 146 (DW_TAG_inlined_subroutine)
<11><a86b7>: Abbrev Number: 146 (DW_TAG_inlined_subroutine)
<4><a86e3>: Abbrev Number: 146 (DW_TAG_inlined_subroutine)
<5><a86f2>: Abbrev Number: 279 (DW_TAG_inlined_subroutine)
<4><a8702>: Abbrev Number: 146 (DW_TAG_inlined_subroutine)
<4><a872b>: Abbrev Number: 146 (DW_TAG_inlined_subroutine)
<5><a8744>: Abbrev Number: 146 (DW_TAG_inlined_subroutine)
<6><a875d>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
<7><a8775>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
<8><a878d>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
<9><a87a5>: Abbrev Number: 146 (DW_TAG_inlined_subroutine)
<3><a87c3>: Abbrev Number: 146 (DW_TAG_inlined_subroutine)
<4><a87e4>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
<5><a8806>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
<6><a8828>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
[...]
```

Get informations about `a875d` for example. `grep -A 5` output the 5 lines after the occurence. 

From here, we can see the starting address of the inlined code in the binary with `DW_AT_low_pc`. `DW_AT_high_pc` gives the size (offset) of the inlined code.

```bash
$ objdump -g libMuscatNative.so | grep -A 5 a875d
 <6><a875d>: Abbrev Number: 141 (DW_TAG_inlined_subroutine)
    <a875f>   DW_AT_abstract_origin: <0xfe7e>
    <a8763>   DW_AT_low_pc      : (index: 0xa0): 0x1c0d7
    <a8765>   DW_AT_high_pc     : 0x5
    <a8769>   DW_AT_call_file   : 33
    <a876a>   DW_AT_call_line   : 621
--
    <1a875d>   DW_AT_decl_line   : 168
    <1a875e>   DW_AT_type        : <0x1a8769>
    <1a8762>   DW_AT_declaration : 1
    <1a8762>   DW_AT_external    : 1
    <1a8762>   DW_AT_accessibility: 1   (public)
 <4><1a8763>: Abbrev Number: 9 (DW_TAG_formal_parameter)
 [...]
```


```bash
$ cat disasm.txt
[...]
muscat/muscat-env/include/eigen3/Eigen/src/Core/CommaInitializer.h:67
    if (m_col==m_xpr.cols())
   b53f2:	xor    %edi,%edi
   b53f4:	cmp    %rsi,%rax
   b53f7:	sete   %dil
   b53fb:	cmove  %rcx,%rax
   b53ff:	add    %r8,%rdi
[...]
```

