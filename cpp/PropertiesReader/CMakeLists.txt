set(target_name PropertiesReader)

set(${target_name}_src  MaterialPropertiesReader.cpp
                        MeshPropertiesReader.cpp
                        SimulationPropertiesReader.cpp
)

set(${target_name}_hpp  PropertiesReaderBase.hpp
                        MaterialPropertiesReader.hpp
                        MeshPropertiesReader.hpp
                        SimulationPropertiesReader.hpp
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