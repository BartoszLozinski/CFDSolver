#pragma once

#include <array>
#include <string>

#include "../Properties/MaterialProperties.hpp"
// Right now only for material properties class
// when other properties will be needed
// it will be refactored

class MaterialPropertiesReader
{
public:
    MaterialProperties ReadFromSetupFile(const std::string& filename = "Setup/MaterialProperties");

};