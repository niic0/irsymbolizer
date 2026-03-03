# Structure
```bash
IRSymbolyzer
├── CMakeLists.txt
├── include/                # Public headers (exposed interfaces)
│   ├── addr2ir/
│   │   └── Addr2IR.h
│   ├── sampler/
│   │   └── Sampler.h
│   └── visualizer/
│       └── Visualizer.h
├── src/                    # Implementation
│   ├── addr2ir/
│   │   └── Addr2IR.cpp
│   ├── sampler/
│   │   └── Sampler.cpp
│   ├── visualizer/
│   │   └── Visualizer.cpp
│   └── main.cpp            # Main entry point (optional tool or CLI)
├── tools/                  # Standalone CLI tools or demos (TODO)
│   ├── run_sampler.cpp
│   └── addr2ir_inspect.cpp
├── data/                   # Test inputs: binaries, .so/.a, fixtures
│   └── gcc7_binary, clang16_binary, stripped_binary, etc.
├── tests/                  # Unit and integration tests (TODO)
│   ├── test_addr2ir.cpp
│   ├── test_sampler.cpp
│   └── test_ir_symbolizer.cpp
├── scripts/                # Helper scripts (build, benchmark, analysis)
│   └── build.sh
└── README.md
```

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
	-DLLVM_INSTALL_UTILS=ON
$ ninja -C <build_path> install
```

# Building the project
```bash
cmake -B <builddir> -G <generator>
```

If not in the system, the LLVM's cmake path must be set by adding the flag `-DLLVM_DIR` such as:
```bash
cmake -B <builddir> -G <generator> -DLLVM_DIR=<llvmdir>
```

The LLVM documentation state that the cmake file could be find in two different locations:
- `<LLVM_INSTALL_PACKAGE_DIR>/LLVMConfig.cmake` where `<LLVM_INSTALL_PACKAGE_DIR>` is the location where LLVM CMake modules are installed as part of an installed version of LLVM. This is typically `cmake/llvm/` within the lib directory. On Linux, this is typically /usr/lib/cmake/llvm/LLVMConfig.cmake.
- `<LLVM_BUILD_ROOT>/lib/cmake/llvm/LLVMConfig.cmake` where `<LLVM_BUILD_ROOT>` is the root of the LLVM build tree. Note: this is only available when building LLVM with CMake.

