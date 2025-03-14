add_library(simple_plugin SHARED
    simple_plugin.cc
)

target_include_directories(simple_plugin
    PRIVATE
        ${CMAKE_SOURCE_DIR}/include
)

set(PLUGIN_OUTPUT_DIR "${CMAKE_BINARY_DIR}/plugins")
file(MAKE_DIRECTORY ${PLUGIN_OUTPUT_DIR})

set_target_properties(simple_plugin PROPERTIES
    LIBRARY_OUTPUT_DIRECTORY ${PLUGIN_OUTPUT_DIR}
)
