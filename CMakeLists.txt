cmake_minimum_required(VERSION 3.14)
project(toy_compiler CXX)

set(CMAKE_CXX_STANDARD 14)
#set(SRC_FILE "src" s/tt.h)

set(LLVM_DIR "/usr/local/Cellar/llvm/11.0.0/lib/cmake/llvm")

if (CMAKE_HOST_SYSTEM_NAME MATCHES "Darwin")
    execute_process(
            COMMAND brew --prefix bison
            RESULT_VARIABLE BREW_BISON
            OUTPUT_VARIABLE BREW_BISON_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_BISON EQUAL 0 AND EXISTS "${BREW_BISON_PREFIX}")
        message(STATUS "Found Bison keg installed by Homebrew at ${BREW_BISON_PREFIX}")
        set(BISON_EXECUTABLE "${BREW_BISON_PREFIX}/bin/bison")
    endif ()

    execute_process(
            COMMAND brew --prefix flex
            RESULT_VARIABLE BREW_FLEX
            OUTPUT_VARIABLE BREW_FLEX_PREFIX
            OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if (BREW_FLEX EQUAL 0 AND EXISTS "${BREW_FLEX_PREFIX}")
        message(STATUS "Found Flex keg installed by Homebrew at ${BREW_FLEX_PREFIX}")
        set(FLEX_EXECUTABLE "${BREW_FLEX_PREFIX}/bin/flex")
    endif ()
endif ()

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

include_directories(${LLVM_INCLUDE_DIRS})
#include_directories("include")

separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

BISON_TARGET(parser
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.tab.cc)
FLEX_TARGET(lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lex.l
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lex.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_compile_options(-w)

add_executable(toy_compiler main.cpp
        src/ast.cc src/ast.h src/IR.cpp src/IR.h src/scanner.h src/tt.h src/types.cuh
        ${FLEX_lexer_OUTPUTS} ${BISON_parser_OUTPUTS})

# Link against LLVM libraries
target_link_libraries(toy_compiler LLVM)