cmake_minimum_required(VERSION 3.28)
project(CFDSolver)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FLAGS -Wall -Werror -Wextra -Wpedantic -Og)

add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(Core/Mesh)

target_link_libraries(${PROJECT_NAME}   PRIVATE     Mesh)

target_compile_options(${PROJECT_NAME}  PRIVATE     ${FLAGS})
set_target_properties(${PROJECT_NAME}   PROPERTIES  CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
