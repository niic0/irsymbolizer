cmake_minimum_required(VERSION 3.16)
project(IRSymbolizer)

# Enable C++17 or newer (add -Wall -Wextra flags)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Locate LLVM
find_package(LLVM REQUIRED CONFIG)

# LLVM's include and recommended definitions
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

llvm_map_components_to_libnames(llvm_libs
  Support
  Option
  DebugInfoDWARF
  Symbolize
  Object
)

add_subdirectory(src/addr2ir)
add_subdirectory(src/sampler)
add_subdirectory(src/visualizer)
add_subdirectory(src/cli)

add_executable(IRSymbolizer src/main.cpp)
target_link_libraries(IRSymbolizer PRIVATE addr2ir cli)

enable_testing()

# Custom test script for each binary
add_test(NAME RunSymbolizerTest
         COMMAND ${CMAKE_SOURCE_DIR}/test/symbolizeCodeWrapper/run_symbolizer_test.sh
         $<TARGET_FILE:IRSymbolizer>
         ${CMAKE_SOURCE_DIR}/test/inputs
         ${CMAKE_SOURCE_DIR}/test/expected)
