add_library(
    genetics
    "${CMAKE_CURRENT_SOURCE_DIR}/population.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/population.cpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/agent.hpp"
    "${CMAKE_CURRENT_SOURCE_DIR}/agent.cpp"
)
set_property(TARGET parser PROPERTY CXX_STANDARD 20)

target_include_directories(genetics PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")