add_library(
    util
    "${CMAKE_CURRENT_SOURCE_DIR}/variant_util.hpp"
)
set_property(TARGET util PROPERTY CXX_STANDARD 20)
set_target_properties(util PROPERTIES LINKER_LANGUAGE CXX)

target_include_directories(util PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")