#include "MaterialPropertiesReader.hpp"

#include <algorithm>
#include <filesystem>
#include <format>
#include <fstream>
#include <ranges>
#include <stdexcept>
#include <sstream>

std::array<double, 3> MaterialPropertiesReader::ReadFromSetupFile(const std::string& filename /* = "Setup/MaterialProperties" */)
{
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
            const auto foundProperty = std::ranges::find_if(propertiesToFind, [&](const auto& prop){ return prop.name == key; });
            if (foundProperty != propertiesToFind.end())
                foundProperty->value = std::stod(valueStr);
        }
        catch (const std::exception&)
        {
            throw std::runtime_error(std::format("Invalid numeric value for property '{}' in file {}", key, filename));
        }
    }

    return { propertiesToFind[0].value, propertiesToFind[1].value, propertiesToFind[2].value };
}