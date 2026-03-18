cmake_minimum_required(VERSION 3.16)
project(IRSymbolizer)

# Enable C++17 or newer (add -Wall -Wextra flags)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Optional components.
option(IRSYMBOLIZER_ENABLE_TUI "Build the optional text UI (requires FTXUI)" OFF)

# Set -O3 for RelWithDebInfo
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO "-O3 -g" CACHE STRING "" FORCE)

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

# Source locations
add_subdirectory(src/addr2ir)
add_subdirectory(src/sampler)
add_subdirectory(src/visualizer)
add_subdirectory(src/cli)

if(IRSYMBOLIZER_ENABLE_TUI)
  if(NOT EXISTS ${CMAKE_SOURCE_DIR}/external/FTXUI/CMakeLists.txt)
    message(FATAL_ERROR
      "IRSYMBOLIZER_ENABLE_TUI=ON but external/FTXUI was not found. "
      "Clone FTXUI into external/FTXUI before enabling the TUI.")
  endif()
  add_subdirectory(external/FTXUI EXCLUDE_FROM_ALL)
  add_subdirectory(src/tui)
endif()

# Executable name
add_executable(IRSymbolizer src/main.cpp)

# Prefix linker-only flags
target_link_libraries(IRSymbolizer PRIVATE addr2ir cli)
if(IRSYMBOLIZER_ENABLE_TUI)
  target_link_libraries(IRSymbolizer PRIVATE tui)
endif()

enable_testing()

# Custom test script for each binary
add_test(NAME RunSymbolizerTest
         COMMAND ${CMAKE_SOURCE_DIR}/test/symbolizeCodeWrapper/run_symbolizer_test.sh
         $<TARGET_FILE:IRSymbolizer>
         ${CMAKE_SOURCE_DIR}/test/inputs
         ${CMAKE_SOURCE_DIR}/test/expected)
