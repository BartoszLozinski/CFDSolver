#pragma once

#include <string>
#include "../Properties/MaterialProperties.hpp"
#include "PropertiesReaderBase.hpp"

// Right now only for material properties class
// when other properties will be needed
// it will be refactored
class MaterialPropertiesReader : public PropertiesReaderBase<MaterialPropertiesReader>
{
friend PropertiesReaderBase<MaterialPropertiesReader>;

protected:
    PropertiesMap CreatePropertiesMap_Impl(MaterialProperties& propertiesStruct) const
    {
        return std::map<std::string, Var>{ 
            {"thermalConductivity", propertiesStruct.thermalConductivity},
            {"specificHeatCapacity", propertiesStruct.specificHeatCapacity},
            {"density", propertiesStruct.density}
        };
    };

public:
    MaterialPropertiesReader() = default;
    MaterialProperties ReadFromSetupFile(const std::string& filename = "Setup/MaterialProperties");
};
