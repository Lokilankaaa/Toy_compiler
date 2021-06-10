cmake_minimum_required(VERSION 3.17)
project(toy_compiler)

set(CMAKE_CXX_STANDARD 17)

set(SRC_FILE "src" src/CodeGenerator.cpp src/CodeGenerator.h)

add_executable(toy_compiler main.cpp ${SRC_FILE})
