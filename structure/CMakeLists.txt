add_library(
    structure
    "${CMAKE_CURRENT_SOURCE_DIR}/node.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/node.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/program.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/program.cpp"
)
set_property(TARGET structure PROPERTY CXX_STANDARD 20)

target_include_directories(structure PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")