cmake_minimum_required(VERSION 3.13)
project(parallel_programming)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -fopenmp")
set(SOURCE_FILES task2.cpp)
add_executable(task1 task1)
add_executable(task2 task2)