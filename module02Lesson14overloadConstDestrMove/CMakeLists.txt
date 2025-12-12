cmake_minimum_required(VERSION 3.5)

project(Containers)

add_executable(myVector myVector.cpp)
set_target_properties(myVector PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)

add_executable(myList myList.cpp)
set_target_properties(myList PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
