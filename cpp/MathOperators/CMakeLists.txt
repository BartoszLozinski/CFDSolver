set(target_name MathOperators)

set(${target_name}_src  Laplacian.cpp
                        LinearAlgebra/GaussElimination.cpp
                        LinearAlgebra/GaussSeidel.cpp
                        LinearAlgebra/ListOfLists.cpp)

set(${target_name}_hpp  Laplacian.hpp
                        LinearAlgebra/GaussElimination.hpp
                        LinearAlgebra/GaussSeidel.hpp
                        LinearAlgebra/ListOfLists.hpp)

configure_library(${target_name}
    SOURCES ${${target_name}_src}
    HEADERS ${${target_name}_hpp}    
)

configure_target(${target_name})