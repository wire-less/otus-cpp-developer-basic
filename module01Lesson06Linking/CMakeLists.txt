cmake_minimum_required(VERSION 3.5)

project(06.guessnumber)

add_executable(guessnumber
	guessnumber.cpp
)

set_target_properties(guessnumber PROPERTIES
	CXX_STANDARD 17
	CXX_STANDARD_REQUIRED ON
)

# ##############################################################################

add_subdirectory(lib)

target_include_directories(guessnumber PRIVATE
	${CMAKE_SOURCE_DIR}/lib
)
target_link_libraries(guessnumber PRIVATE
	guess_lib
)
