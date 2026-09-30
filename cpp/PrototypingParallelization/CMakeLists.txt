set(target_name PrototypingParallelization)

set(${target_name}_src  Parallel.cpp
)

set(${target_name}_hpp  Parallel.hpp
)

configure_library(${target_name}
    SOURCES ${${target_name}_src}
    HEADERS ${${target_name}_hpp}    
)

configure_target(${target_name})

target_link_libraries(${target_name}
    PRIVATE
        Field
        MathOperators
        Mesh
        BoundaryCondition
        ResultsExporter
    INTERFACE
        Properties
)
