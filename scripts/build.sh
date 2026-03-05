#!/bin/bash

cmake -B build -G Ninja \
      -DCMAKE_BUILD_TYPE=RelWithDebInfo \
      -DLLVM_DIR=external/llvm-project/build/lib/cmake/llvm \
      -DCMAKE_CXX_COMPILER=clang++ \
