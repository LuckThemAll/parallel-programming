cmake_minimum_required(VERSION 3.13)

find_package(MPI REQUIRED)

add_executable(task1 task1.cpp)

include_directories(task1 ${MPI_CXX_INCLUDE_PATH})
target_link_libraries(task1 ${MPI_CXX_LIBRARIES})

