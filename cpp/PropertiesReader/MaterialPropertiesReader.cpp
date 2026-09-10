#include "MaterialPropertiesReader.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <format>
#include <map>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <variant>

MaterialProperties MaterialPropertiesReader::ReadFromSetupFile(const std::string& filename /* = "Setup/MaterialProperties" */)
{
    return ParsePropertiesFile<MaterialProperties>(filename);
}
