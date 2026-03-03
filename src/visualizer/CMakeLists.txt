add_library(visualizer STATIC
  visualizer.cpp
)

target_include_directories(visualizer
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(visualizer
  PRIVATE
    LLVMObject
    LLVMSymbolize
    LLVMDebugInfoDWARF
)
