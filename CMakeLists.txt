cmake_minimum_required(VERSION 3.17)
project(toy_compiler)

set(CMAKE_CXX_STANDARD 17)

add_executable(toy_compiler main.cpp src/scanner.h src/ast.h src/types.cuh src/symtab.cpp src/symtab.h src/driver.cpp src/driver.h)