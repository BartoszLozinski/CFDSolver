#pragma once

#include <string>
#include <map>
#include <variant>
#include <functional>

#include "../Properties/MeshProperties.hpp"

class MeshPropertiesReader
{
public:
    MeshProperties ReadFromSetupFile(const std::string& filename = "Setup/MeshProperties");
};
