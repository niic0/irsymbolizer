#!/bin/bash

cmake -B build -G Ninja \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DIRSYMBOLIZER_ENABLE_TUI=ON \
      -DLLVM_DIR=external/llvm-project/build/lib/cmake/llvm \
      -DCMAKE_CXX_COMPILER=clang++ \
