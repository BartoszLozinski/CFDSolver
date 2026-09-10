#pragma once

#include <string>
#include "../Properties/MeshProperties.hpp"

class MeshPropertiesReader
{
public:
    MeshProperties ReadFromSetupFile(const std::string& filename = "Setup/MeshProperties");
};
