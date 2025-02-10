find_package(Ruby REQUIRED 3.0)

set(TARGET hDSL_generated_lib)

set(hDSL_GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
set(hDSL_GENERATED_SRC "${hDSL_GENERATED_DIR}/executors.cc")

add_custom_target(${TARGET} ALL DEPENDS ${hDSL_GENERATED_SRC})

add_custom_command(
    OUTPUT ${hDSL_GENERATED_SRC}
    COMMAND ${RUBY_EXECUTABLE} ${CMAKE_SOURCE_DIR}/scripts/codegen.rb ${hDSL_GENERATED_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating architecture-specific implementation from hDSL"
)

add_library(hDSL-lib STATIC ${hDSL_GENERATED_SRC})

set(hDSL_GENERATED_DIR ${hDSL_GENERATED_DIR} PARENT_SCOPE)