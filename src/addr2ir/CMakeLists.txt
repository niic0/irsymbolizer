add_library(addr2ir STATIC
  addr2ir.cpp
)

target_include_directories(addr2ir
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(addr2ir
  PRIVATE
    LLVMObject
    LLVMSymbolize
    LLVMDebugInfoDWARF
)
