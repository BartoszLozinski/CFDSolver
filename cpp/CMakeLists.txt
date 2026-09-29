cmake_minimum_required(VERSION 3.28)
project(CFDSolver)

include(${CMAKE_SOURCE_DIR}/cmake/configuration.cmake)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CORE_FLAGS  -Wall
                -Wextra
                -Wpedantic
                -Werror)
            
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(BoundaryCondition)
add_subdirectory(MathOperators)
add_subdirectory(Mesh)
add_subdirectory(Field)
add_subdirectory(Properties)
add_subdirectory(PropertiesReader)
add_subdirectory(Solvers)
add_subdirectory(ResultsExporter)

add_subdirectory(UnitTests)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Mesh
        HeatConductionSolver
        PropertiesReader
)

configure_target(${PROJECT_NAME})