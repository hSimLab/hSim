cmake_minimum_required(VERSION 3.19)

project(hSim)

include(cmake/CPM.cmake)
# Provide default CXX settings
include(cmake/defaults.cmake)

add_subdirectory(third_party)
add_subdirectory(scripts)

set(hSIM_LIB
    src/memory.cc src/machine.cc
    #
    src/elf_loader.cc)

add_library(hSim-lib STATIC ${hSIM_LIB})

target_include_directories(hSim-lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(
  hSim-lib
  PUBLIC hDSL-lib
  PRIVATE elfio::elfio hSIM::defaults)

add_executable(${PROJECT_NAME} src/main.cc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wpedantic)
target_link_libraries(${PROJECT_NAME} PRIVATE hSim-lib CLI11::CLI11 fmt::fmt)
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME hsim)
