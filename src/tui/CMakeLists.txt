add_library(tui STATIC
  tui.cpp
)

target_include_directories(tui
  PUBLIC
    ${PROJECT_SOURCE_DIR}/include
)

target_link_libraries(tui
  PRIVATE
    ftxui::component
)
