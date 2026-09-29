function(configure_target target)


    # Static libs for now, to be extended for header only interfaces
    target_compile_options(${target}
        PRIVATE
            -Wall
            -Wextra
            -Werror
            -Wpedantic

            $<$<CONFIG:DEBUG>: -Og -g>
            $<$<CONFIG:RELEASE>: -O3>
    )

    set_target_properties(${target}
        PROPERTIES
            CXX_STANDARD 20
            CXX_STANDARD_REQUIRED ON
            CXX_EXTENSIONS OFF
    )


endfunction()


function(configure_library target)


    set(options HEADER_ONLY)
    set(multiValueArgs SOURCES HEADERS)
    cmake_parse_arguments(ARG "${options}" "" "${multiValueArgs}" ${ARGN})
    cmake_path(GET CMAKE_CURRENT_SOURCE_DIR     PARENT_PATH     parent_dir)

    add_library(${target} STATIC)
    target_sources(${target}
        PRIVATE
            ${ARG_SOURCES}
        PUBLIC
            FILE_SET HEADERS
            BASE_DIRS ${parent_dir}
            FILES ${ARG_HEADERS}
    )


endfunction()
