#include "SimulationPropertiesReader.hpp"

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <format>
#include <map>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <variant>

SimulationProperties SimulationPropertiesReader::ReadFromSetupFile(const std::string& filename)
{
    SimulationProperties output;

    using DoubleRef = std::reference_wrapper<double>;
    using BoolRef = std::reference_wrapper<bool>;
    using UIntRef = std::reference_wrapper<uint32_t>;
    using Var = std::variant<DoubleRef, BoolRef, UIntRef>;

    std::map<std::string, Var> propertiesMap = {
        {"dt", DoubleRef(output.dt)},
        {"shouldExportResults", BoolRef(output.shouldExportResults)},
        {"exportFrequency", UIntRef(output.exportFrequency)},
        {"timesteps", UIntRef(output.timesteps)}
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
        if (line.front() == '#')
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
                else if constexpr (std::is_same_v<T, uint32_t>)
                {
                    unsigned long v = std::stoul(valueStr);
                    ref.get() = static_cast<uint32_t>(v);
                }
                else if constexpr (std::is_same_v<T, bool>)
                {
                    std::ranges::transform( valueStr, valueStr.begin()
                                          , [](unsigned char c){ return std::tolower(c); });

                    ref.get() = valueStr == "true" ? true : false;
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
