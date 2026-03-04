set(target_name Mesh)

set(${target_name}_src      StructuredMesh.cpp)
set(${target_name}_hpp      StructuredMesh.hpp
                            Field.hpp)

add_library(${target_name} STATIC)

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH parent_path)

target_sources(${target_name}
    PRIVATE
        ${${target_name}_src}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${parent_path}
        FILES ${${target_name}_hpp}
)

target_compile_options(${target_name}  PRIVATE ${FLAGS}
                                                $<$<CONFIG:DEBUG>:-Og -g>
                                                $<$<CONFIG:RELEASE>:-O3>)
                                                
set_target_properties(${target_name} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
