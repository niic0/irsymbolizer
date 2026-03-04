add_library(cli STATIC
  cli.cpp
)

target_include_directories(cli
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(cli
  PRIVATE
  LLVMOption
)
