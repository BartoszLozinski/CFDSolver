cmake_minimum_required(VERSION 3.28)
project(CFDSolver)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CORE_FLAGS  -Wall
                -Wextra
                -Wpedantic
                -Werror)

add_subdirectory(BoundaryCondition)
add_subdirectory(Mesh)
add_subdirectory(Solvers)