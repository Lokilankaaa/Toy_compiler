cmake_minimum_required(VERSION 3.14)
project(toy_compiler CXX)

set(CMAKE_CXX_STANDARD 14)
set(SRC_FILE "src/" "src/ast.cpp")

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

include_directories("/usr/local/Cellar/llvm/11.0.0/include/")

set(LLVM_DIR "/usr/local/Cellar/llvm/11.0.0/lib/cmake/llvm")

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)
find_package(LLVM REQUIRED)

link_directories(${LLVM_LIBRARY_DIRS})

BISON_TARGET(parser
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.y
        ${CMAKE_CURRENT_SOURCE_DIR}/src/parser.tab.cc)
FLEX_TARGET(lexer
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lex.l
        ${CMAKE_CURRENT_SOURCE_DIR}/src/lex.yy.cc)
ADD_FLEX_BISON_DEPENDENCY(lexer parser)

add_compile_options(-w)

add_executable(toy_compiler main.cpp ${SRC_FILE} ${FLEX_lexer_OUTPUTS} ${BISON_parser_OUTPUTS})

target_link_libraries(toy_compiler LLVM)


