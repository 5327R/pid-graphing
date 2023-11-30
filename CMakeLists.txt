cmake_minimum_required(VERSION 3.1)

project(pidtest VERSION 1.0
                DESCRIPTION "test pids"
                LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

add_subdirectory(matplotplusplus)
add_subdirectory(src)


