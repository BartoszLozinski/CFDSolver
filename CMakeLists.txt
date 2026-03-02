cmake_minimum_required(VERSION 3.28)
project(CFDApp)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_EXTENSIONS OFF)

set(FLAGS   -Wall -Werror -Wpedantic -Wextra)

add_executable(${PROJECT_NAME}  main.cpp)

target_compile_options(${PROJECT_NAME}  PRIVATE ${FLAGS}
                                                $<$<CONFIG:DEBUG>:-Og -g>
                                                $<$<CONFIG:RELEASE>:-O3>)
                                                
set_target_properties(${PROJECT_NAME} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
