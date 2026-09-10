#pragma once

#pragma once

#include <string>
#include "../Properties/SimulationProperties.hpp"
#include "PropertiesReaderBase.hpp"

class SimulationPropertiesReader : public PropertiesReaderBase<SimulationPropertiesReader>
{
friend PropertiesReaderBase<SimulationPropertiesReader>;

protected:
    PropertiesMap CreatePropertiesMap_Impl(SimulationProperties& propertiesStruct) const;

public:
    SimulationPropertiesReader() = default;
    SimulationProperties ReadFromSetupFile(const std::string& filename = "Setup/SimulationProperties") const;
};
