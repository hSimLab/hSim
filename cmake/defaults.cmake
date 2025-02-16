set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(TARGET hSIM-defaults)

add_library(${TARGET} INTERFACE)

target_compile_features(${TARGET} INTERFACE cxx_std_20)

# Compile stuff
target_compile_options(${TARGET} INTERFACE -Wall -Wextra -Wpedantic
                                           -Wold-style-cast -Wvla -Werror)

add_library(hSIM::defaults ALIAS ${TARGET})
