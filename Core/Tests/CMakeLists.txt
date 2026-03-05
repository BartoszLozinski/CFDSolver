set(target_name UnitTests)

set(${target_name}_src   UnitTests.cpp)

find_package(GTest REQUIRED)
set(GMOCK_LIBRARIES /usr/lib/libgmock.a /usr/lib/libgmock_main.a)

add_executable(${target_name} ${${target_name}_src})

target_link_libraries(${target_name}   PRIVATE      Mesh
                                                    FVM
                                                    ${GTEST_LIBRARIES}
                                                    ${GMOCK_LIBRARIES})

target_compile_options(${target_name}  PRIVATE ${FLAGS}
                                                $<$<CONFIG:DEBUG>:-Og -g>
                                                $<$<CONFIG:RELEASE>:-O3>)

set_target_properties(${target_name} PROPERTIES CXX_STANDARD 20 CXX_STANDARD_REQUIRED ON)
