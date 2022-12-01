cmake_minimum_required(VERSION 3.19)
project(AdventOfCode LANGUAGES CXX VERSION 0.0.1)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED true)

add_subdirectory(externals/googletest)
enable_testing()

add_subdirectory(src)
