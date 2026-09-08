#include "MaterialPropertiesReader.hpp"

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <map>
#include <ranges>
#include <stdexcept>
#include <sstream>

MaterialProperties MaterialPropertiesReader::ReadFromSetupFile(const std::string& filename /* = "Setup/MaterialProperties" */)
{
    MaterialProperties output;
    std::map<std::string, double&> propertiesMap = { {"thermalConductivity", output.thermalConductivity}
                                                   , {"specificHeatCapacity", output.specificHeatCapacity}
                                                   , {"density", output.density} };

    std::filesystem::path path = filename;

    std::ifstream inputFile{ path };

    if (!inputFile.is_open())
        throw std::runtime_error(std::format("Failed to open file for reading: {}", filename));

    std::string line{};

    while (std::getline(inputFile, line))
    {
        if (line.empty())
            continue;
        if (line.front() == '#') // comment
            continue;
        if (line == "{" || line == "}")
            continue;


        std::istringstream iss(line);
        std::string key;
        if (!(iss >> key))
            continue;

        std::string valueStr;
        if (!(iss >> valueStr))
            continue;

        if (auto commentPos = valueStr.find('#'); commentPos != std::string::npos)
            valueStr = valueStr.substr(0, commentPos);

        try
        {   
            propertiesMap.at(key) = std::stod(valueStr);
        }
        catch (const std::exception&)
        {
            throw std::runtime_error(std::format("Invalid numeric value for property '{}' in file {}", key, filename));
        }
    }

    return output;
}