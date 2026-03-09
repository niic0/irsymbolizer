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

If not in the system, the LLVM's cmake build or install path must be set by adding the flag `-DLLVM_DIR` such as:
```bash
cmake -B <builddir> -G <generator> -DLLVM_DIR=<llvmdir>
```

The LLVM documentation state that the cmake file could be find in two different locations:
- `<LLVM_INSTALL_PACKAGE_DIR>/LLVMConfig.cmake` where `<LLVM_INSTALL_PACKAGE_DIR>` is the location where LLVM CMake modules are installed as part of an installed version of LLVM. This is typically `cmake/llvm/` within the lib directory. On Linux, this is typically /usr/lib/cmake/llvm/LLVMConfig.cmake.
- `<LLVM_BUILD_ROOT>/lib/cmake/llvm/LLVMConfig.cmake` where `<LLVM_BUILD_ROOT>` is the root of the LLVM build tree. Note: this is only available when building LLVM with CMake.

**Note that LLVM needs to be build with the flag `-DLLVM_ENABLE_RTTI=ON`**

# Requirements
## LLVM
Build of LLVM, needs to have `LLVM_INSTALL_UTILS` flag. Ninja bellow but could be any generator (Make etc.)

ref: https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project


**LLVM build commands example:**
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
