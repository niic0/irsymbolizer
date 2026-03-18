add_library(addr2ir STATIC
  samples2ir.cpp
)

target_include_directories(samples2ir
  PUBLIC
  ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(samples2ir
  PRIVATE
  LLVMObject
  LLVMSymbolize
  LLVMDebugInfoDWARF
)
