cmake_minimum_required(VERSION 3.19)

project(hSim)

include(cmake/CPM.cmake)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(third_party)

add_executable(${PROJECT_NAME} src/main.cc)

target_compile_options(${PROJECT_NAME} PRIVATE -Wpedantic)
target_link_libraries(${PROJECT_NAME} PRIVATE 
    CLI11::CLI11
    elfio::elfio
    fmt::fmt
)