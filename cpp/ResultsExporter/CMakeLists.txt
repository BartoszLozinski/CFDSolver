set(target_name ResultsExporter)

set(${target_name}_src  CSVExporter.cpp
)

set(${target_name}_hpp  CSVExporter.hpp
)

configure_library(${target_name}
    SOURCES ${${target_name}_src}
    HEADERS ${${target_name}_hpp}    
)

configure_target(${target_name})
