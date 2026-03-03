add_library(sampler STATIC
  sampler.cpp
)

target_include_directories(sampler
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(sampler
  PRIVATE
    LLVMObject
    LLVMSymbolize
    LLVMDebugInfoDWARF
)
