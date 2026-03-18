# Usage
```bash
--sample / -s <bin>                        : Sample the binary with a default frequency of 200Hz
--freq / -f <freq>                         : Change the default frequency. Used if sample or no argument are used.
--addr2line / -l <bin> <address>           :
                 <bin> <samples_addr_file> :
--addr2ir / -i <bin> <address>             : Give the LLVM IR line(s) of an address in a binary
	           <bin> <samples_addr_file>   : Give
--output-addr2line <format> <name>         : Output the addr2line result in the format and the name of choice.
                                             <format> can be csv or txt.
--output-addr2ir <format> <name>           : Output the addr2ir result in the format and the name of choice.
                                             <format> can be csv or txt
--output-samples <format> <name>           : Output the sampling result in the format and the name of choice.
                                             <format> can be csv or txt
```

# Building the project
```bash
cmake -B <builddir> -G <generator>
```

# Requirements
## LLVM
Build of [LLVM](https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project), needs to have `LLVM_INSTALL_UTILS` and `LLVM_ENABLE_RTTI=ON` flag.

**LLVM build commands example:**

(Ninja compilation but could be any generator)

```bash
$ git clone https://github.com/llvm/llvm-project.git
$ cd llvm-project
$ cmake -G Ninja -S <llvm_project_path> -B <build_path> \
	-DCMAKE_INSTALL_PREFIX=<install_prefix_path> \
	-DCMAKE_BUILD_TYPE=Release \
	-DLLVM_INSTALL_UTILS=ON \
	-DLLVM_ENABLE_RTTI=ON
$ ninja -C <build_path> install
```

If not in the system, the LLVM's cmake build or install path must be set by adding the flag `-DLLVM_DIR` such as:
```bash
cmake -B <builddir> -G <generator> -DLLVM_DIR=<llvmdir>
```

The LLVM documentation state that the cmake file could be find in two different locations:
- `<LLVM_INSTALL_PACKAGE_DIR>/LLVMConfig.cmake` where `<LLVM_INSTALL_PACKAGE_DIR>` is the location where LLVM CMake modules are installed as part of an installed version of LLVM. This is typically `cmake/llvm/` within the lib directory. On Linux, this is typically /usr/lib/cmake/llvm/LLVMConfig.cmake.
- `<LLVM_BUILD_ROOT>/lib/cmake/llvm/LLVMConfig.cmake` where `<LLVM_BUILD_ROOT>` is the root of the LLVM build tree. Note: this is only available when building LLVM with CMake.

## Optional TUI (disabled by default)
The text-based UI depends on [FTXUI](https://github.com/ArthurSonzogni/FTXUI) and is not required for the rest of the project, so it is **disabled by default**. To build it:

1. Fetch FTXUI (into `external/ftxui` for example):
   ```bash
   git clone https://github.com/ArthurSonzogni/FTXUI.git external/ftxui
   ```
2. Enable the component when configuring CMake:
   ```bash
   # in project root directory
   cd <project_root_directory>
   cmake -B <builddir> -G <generator> -DIRSYMBOLIZER_ENABLE_TUI=ON
   ```

If `IRSYMBOLIZER_ENABLE_TUI` is not set, the TUI target is skipped entirely and no FTXUI sources are required.

# Structure
```bash
IRSymbolyzer
├── CMakeLists.txt
├── artifacts/              # Perf output, not versionned
│   └── perf/
├── benchmarks/             # Performance experiements, outputs in 
│                           # benchmarks/perf directory
├── data/                   # Inputs for test purpose
├── include/                # Public headers (exposed interfaces)
├── src/                    # Implementation
├── data/                   # Test inputs: binaries, .so/.a ...
├── tests/                  # Unit and integration tests (TODO)
├── scripts/                # Helper scripts (build, benchmark, analysis)
│   └── build.sh
└── README.md
```

