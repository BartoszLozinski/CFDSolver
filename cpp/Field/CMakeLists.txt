set(target_name Field)

set(${target_name}_src  Field.cpp)
set(${target_name}_hpp  Field.hpp)

configure_library(${target_name}
    SOURCES ${${target_name}_src}
    HEADERS ${${target_name}_hpp}    
)

configure_target(${target_name})

target_link_libraries(${target_name}
    PRIVATE
        BoundaryCondition
        Mesh
)