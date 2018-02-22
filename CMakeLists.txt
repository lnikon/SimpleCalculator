cmake_minimum_required(VERSION 3.0.0)
project(simplecalc)

set(simplecalc_VERSION_MAJOR 1.0)
set(simplecalc_VERSION_MINOR 0.0)

set(GCC_COVERAGE_COMPILE_FLAGS "-Wall -O2 -std=c++14")

add_definitions(${GCC_COVERAGE_COMPILE_FLAGS})

include_directories("./include")
file(GLOB SOURCES "./src/*.cpp")

add_executable(main ${SOURCES})

