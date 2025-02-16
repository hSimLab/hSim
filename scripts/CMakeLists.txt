find_package(Ruby 3.0 REQUIRED)

set(TARGET hDSL_generated_lib)

set(hDSL_GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
set(hDSL_GENERATED_SRC "${hDSL_GENERATED_DIR}/executors.cc")

set(hDSL_GENERATED_HEADERS executors.hh cpu_state.hh decoder.hh)
list(TRANSFORM hDSL_GENERATED_HEADERES PREPEND ${hDSL_GENERATED_DIR})

set(hDSL_GEN_SCRIPT "${CMAKE_CURRENT_SOURCE_DIR}/codegen.rb")

set(hDSL_GENERATED_FILES ${hDSL_GENERATED_SRC} ${hDSL_GENERATED_HEADERS})

add_custom_command(
    OUTPUT ${hDSL_GENERATED_FILES}
    COMMAND ${RUBY_EXECUTABLE} ${hDSL_GEN_SCRIPT} ${hDSL_GENERATED_DIR}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    DEPENDS ${hDSL_GEN_SCRIPT}
    COMMENT "Generating architecture-specific implementation from hDSL"
    VERBATIM
  )

add_library(hDSL-lib STATIC ${hDSL_GENERATED_FILES})
target_include_directories(hDSL-lib PUBLIC ${hDSL_GENERATED_DIR})

