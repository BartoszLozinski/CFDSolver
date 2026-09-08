set(target_name Properties)

set(${target_name}_hpp  MaterialProperties.hpp
                        MeshProperties.hpp
)

add_library(${target_name} INTERFACE)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR     PARENT_PATH     PROPERTIES_PARENT_DIR)

target_sources(${target_name}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${PROPERTIES_PARENT_DIR}
        FILES ${${target_name}_hpp}
)

target_compile_options(${target_name}
    INTERFACE
        ${CORE_FLAGS}
        $<$<CONFIG:DEBUG>: -Og -g>
        $<$<CONFIG:RELEASE>: -O3>
)

set_target_properties(${target_name}
    PROPERTIES
        CXX_STANDARD 20
        CXX_STANDARD_REQUIRED ON
)