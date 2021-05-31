cmake_minimum_required(VERSION 3.17)
project(toy_compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(toy_compiler main.cpp scanner.h ast.cpp ast.h types.cuh)