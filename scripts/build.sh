#!/bin/bash

cmake -B build -G Ninja -DLLVM_DIR=external/llvm-project/build/lib/cmake/llvm
