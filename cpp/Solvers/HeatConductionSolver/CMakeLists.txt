set(target_name HeatConductionSolver)

set(${target_name}_src  SolverBase.cpp
                        ExplicitHeatConduction.cpp
                        ImplicitHeatConduction.cpp
)

set(${target_name}_hpp  SolverBase.hpp
                        ExplicitHeatConduction.hpp
                        ImplicitHeatConduction.hpp
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
        PrototypingParallelization
    INTERFACE
        Properties
)
