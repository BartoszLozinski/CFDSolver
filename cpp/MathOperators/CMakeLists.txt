set(target_name MathOperators)

set(${target_name}_src  Laplacian.cpp
                        LinearAlgebra/GaussElimination.cpp
                        LinearAlgebra/GaussSeidel.cpp)
set(${target_name}_hpp  Laplacian.hpp
                        LinearAlgebra/GaussElimination.hpp
                        LinearAlgebra/GaussSeidel.hpp)

add_library(${target_name}  STATIC)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR     PARENT_PATH     MATH_OPERATORS_PARENT_DIR)

target_sources(${target_name}
    PRIVATE
        ${${target_name}_src}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${MATH_OPERATORS_PARENT_DIR}
        FILES ${${target_name}_hpp}
)

target_compile_options(${target_name}
    PRIVATE
        ${CORE_FLAGS}
        $<$<CONFIG:DEBUG>: -Og -g>
        $<$<CONFIG:RELEASE>: -O3>
)

set_target_properties(${target_name}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)