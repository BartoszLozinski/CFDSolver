set(target_name Mesh)

set(${target_name}_src  MeshGenerator.cpp
)

set(${target_name}_hpp  MeshGenerator.hpp
)

configure_library(${target_name}
    SOURCES ${${target_name}_src}
    HEADERS ${${target_name}_hpp}    
)

configure_target(${target_name})

target_link_libraries(${target_name}
    INTERFACE
        Properties
)
