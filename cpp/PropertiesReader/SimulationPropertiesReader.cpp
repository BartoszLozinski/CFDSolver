#include "SimulationPropertiesReader.hpp"


SimulationPropertiesReader::PropertiesMap SimulationPropertiesReader::CreatePropertiesMap_Impl(SimulationProperties& propertiesStruct) const
    {
        return PropertiesMap{
            {"dt", DoubleRef(propertiesStruct.dt)},
            {"shouldExportResults", BoolRef(propertiesStruct.shouldExportResults)},
            {"exportFrequency", UIntRef(propertiesStruct.exportFrequency)},
            {"timesteps", UIntRef(propertiesStruct.timesteps)}
        };
    };

SimulationProperties SimulationPropertiesReader::ReadFromSetupFile(const std::string& filename /* = "Setup/MaterialProperties" */) const
{
    return ParsePropertiesFile<SimulationProperties>(filename);
}
