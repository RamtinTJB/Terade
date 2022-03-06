cmake_minimum_required(VERSION 3.12)

project(Terade VERSION 1.0 LANGUAGES CXX)

include (cmake/doctest.cmake)

# C++ standard std 17. We can change this to 14
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED True)

add_subdirectory(src)
add_subdirectory(test)
