cmake_minimum_required(VERSION 3.19)

project(hSim)

include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(SUBDIRS third_party scripts)

foreach(DIR ${SUBDIRS})
  add_subdirectory(${DIR})
endforeach()

set(hSIM_LIB
    src/memory.cc
    src/machine.cc
    #
    src/elf_loader.cc
)

add_library(hSim-lib STATIC ${hSIM_LIB})

target_include_directories(hSim-lib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(hSim-lib PUBLIC hDSL-lib PRIVATE elfio::elfio)

add_executable(${PROJECT_NAME} src/main.cc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wpedantic)
target_link_libraries(${PROJECT_NAME} PRIVATE
    hSim-lib
    CLI11::CLI11
    fmt::fmt
)
