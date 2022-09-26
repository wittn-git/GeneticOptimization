add_library(
    parser
    "${CMAKE_CURRENT_SOURCE_DIR}/parser.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/parser.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lexer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/lexer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tokenbuffer.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/tokenbuffer.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/token.hpp"
)
set_property(TARGET parser PROPERTY CXX_STANDARD 20)

target_include_directories(parser PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")