cmake_minimum_required(VERSION 3.0.0)
project(GeneticOptimization VERSION 0.1.0 LANGUAGES CXX)

add_executable(GeneticOptimization main.cpp)
set_property(TARGET GeneticOptimization PROPERTY CXX_STANDARD 20)

add_subdirectory(parser)
target_link_libraries(GeneticOptimization PRIVATE parser)
add_subdirectory(structure)
target_link_libraries(GeneticOptimization PRIVATE structure)