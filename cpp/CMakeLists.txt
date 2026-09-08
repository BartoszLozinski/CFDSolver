cmake_minimum_required(VERSION 3.28)
project(CFDSolver)

set(CMAKE_CXX_COMPILER clang++-18)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CORE_FLAGS  -Wall
                -Wextra
                -Wpedantic
                -Werror)
            
add_executable(${PROJECT_NAME} main.cpp)

add_subdirectory(BoundaryCondition)
add_subdirectory(Mesh)
add_subdirectory(Field)
add_subdirectory(Solvers)
add_subdirectory(ResultsExporter)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        Mesh
        Solvers
        ResultsExporter
)

target_compile_options(${PROJECT_NAME}
    PRIVATE
        ${CORE_FLAGS}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)
