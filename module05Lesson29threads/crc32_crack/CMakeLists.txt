cmake_minimum_required(VERSION 3.20)
project(crc32_crack CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(crc32_crack main.cpp
        CRC32.cpp
        CRC32.hpp
        IO.cpp
        IO.hpp)

if (MSVC)
    target_compile_options(crc32_crack PUBLIC /W4)
else ()
    target_compile_options(crc32_crack PUBLIC -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion)
endif ()