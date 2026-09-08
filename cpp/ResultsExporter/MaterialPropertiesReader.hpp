#pragma once

#include <array>
#include <string>

// Right now only for material properties class
// when other properties will be needed
// it will be refactored

class MaterialPropertiesReader
{
private:
    struct PropertyToFind
    {
        std::string name;
        double value{};
    };

    std::array<PropertyToFind, 3> propertiesToFind{ PropertyToFind{"thermalConductivity", 0.0}
                                                  , PropertyToFind{"specificHeatCapacity", 0.0}
                                                  , PropertyToFind{"density", 0.0} };

public:
    std::array<double, 3> ReadFromSetupFile(const std::string& filename = "Setup/MaterialProperties");

};