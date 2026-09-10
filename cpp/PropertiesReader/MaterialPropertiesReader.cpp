#include "MaterialPropertiesReader.hpp"

MaterialPropertiesReader::PropertiesMap MaterialPropertiesReader::CreatePropertiesMap_Impl(MaterialProperties& propertiesStruct) const
    {
        return PropertiesMap{ 
            {"thermalConductivity", propertiesStruct.thermalConductivity},
            {"specificHeatCapacity", propertiesStruct.specificHeatCapacity},
            {"density", propertiesStruct.density}
        };
    };

MaterialProperties MaterialPropertiesReader::ReadFromSetupFile(const std::string& filename /* = "Setup/MaterialProperties" */) const
{
    return ParsePropertiesFile<MaterialProperties>(filename);
}
