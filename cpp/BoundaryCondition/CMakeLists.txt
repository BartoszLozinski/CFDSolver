set(target_name BoundaryCondition)

set(${target_name}_src  BoundaryConditionBase.cpp
                        Direchlet.cpp
                        Neumann.cpp
)

set(${target_name}_hpp  Direchlet.hpp
                        Neumann.hpp
)

configure_library(${target_name}
    SOURCES ${${target_name}_src}
    HEADERS ${${target_name}_hpp}    
)

configure_target(${target_name})