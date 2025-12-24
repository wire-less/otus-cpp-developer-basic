cmake_minimum_required(VERSION 3.25)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(GoogleTestingFramework)

# Lookup for pre-built gtest
find_package(GTest CONFIG REQUIRED)

# Test target
add_executable(
    testVector
    test/testVector.cpp
)
add_executable(
    testList
    test/testList.cpp
)

# Add src to the include directories for the test target
target_include_directories(
    testVector PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)
target_include_directories(
    testList PRIVATE
    "${CMAKE_CURRENT_SOURCE_DIR}/src"
)

# Link test target against gtest libraries
target_link_libraries(
    testVector PRIVATE
    GTest::gtest_main
    GTest::gtest
)
target_link_libraries(
    testList PRIVATE
    GTest::gtest_main
    GTest::gtest
)

if (MSVC)
    target_compile_options(
        testVector PRIVATE
        /W4
    )
    target_compile_options(
        testList PRIVATE
        /W4
    )
else ()
    target_compile_options(
        testVector PRIVATE
        -Wall -Wextra -pedantic
    )
    target_compile_options(
        testList PRIVATE
        -Wall -Wextra -pedantic
    )
endif()