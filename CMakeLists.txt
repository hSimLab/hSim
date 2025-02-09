cmake_minimum_required(VERSION 3.19)

project(hSim)

include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(third_party)

set(HSIM_LIBRARY
    src/memory.cc
    src/machine.cc
    #
    src/elf_loader.cc
)

add_library(hSim-lib STATIC ${HSIM_LIBRARY})

target_link_libraries(hSim-lib PRIVATE elfio::elfio)

target_include_directories(hSim-lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME} src/main.cc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wpedantic)
target_link_libraries(${PROJECT_NAME} PRIVATE
    hSim-lib
    CLI11::CLI11
    fmt::fmt
)