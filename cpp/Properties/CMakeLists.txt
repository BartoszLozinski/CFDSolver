set(target_name Properties)

set(${target_name}_hpp  MaterialProperties.hpp
                        MeshProperties.hpp
                        SimulationProperties.hpp
)

configure_library(${target_name}
    HEADER_ONLY True
    HEADERS ${${target_name}_hpp}
)

configure_target(${target_name}
    HEADER_ONLY True
)