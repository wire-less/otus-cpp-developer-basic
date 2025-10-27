cmake_minimum_required(VERSION 3.5)

project(06.guessnumber_static_library)

add_library(guess_lib STATIC check_value.cpp high_scores.cpp random_value.cpp)
