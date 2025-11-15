set(target_name Mesh)

set(${target_name}_src  Node.cpp
                        Face.cpp
)

set(${target_name}_hpp  Node.hpp
                        Face.hpp
                        Cell.hpp
)


add_library(${target_name})

cmake_path(GET CMAKE_CURRENT_SOURCE_DIR PARENT_PATH MESH_PARENT_DIR)

target_sources(${target_name}
    PRIVATE
        ${${target_name}_src}
    PUBLIC
        FILE_SET HEADERS
        BASE_DIRS ${MESH_PARENT_DIR}
        FILES ${${target_name}_hpp}
)

target_compile_options(${target_name}  PRIVATE     ${FLAGS})
set_target_properties(${target_name}   PROPERTIES  CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
