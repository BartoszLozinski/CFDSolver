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
    MaterialProperties output;
    
    using DoubleRef = std::reference_wrapper<double>;
    using Var = std::variant<DoubleRef>;

    std::map<std::string, Var> propertiesMap = { 
        {"thermalConductivity", output.thermalConductivity},
        {"specificHeatCapacity", output.specificHeatCapacity},
        {"density", output.density}
    };


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

        auto it = propertiesMap.find(key);
        if (it == propertiesMap.end())
            continue; // unknown property
        
        try
        {
            std::visit([&](auto& ref)
            {
                using T = std::remove_cvref_t<decltype(ref.get())>;
                if constexpr (std::is_same_v<T, double>)
                {
                    ref.get() = std::stod(valueStr);
                }
            }, it->second);
        }
        catch (const std::exception&)
        {
            throw std::runtime_error(std::format("Invalid value for property '{}' in file {}", key, filename));
        }
    }

    return output;
}