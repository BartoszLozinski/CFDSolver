#pragma once

#pragma once

#include <string>
#include "../Properties/SimulationProperties.hpp"

class SimulationPropertiesReader
{
public:
    SimulationProperties ReadFromSetupFile(const std::string& filename = "Setup/SimulationProperties");
};
