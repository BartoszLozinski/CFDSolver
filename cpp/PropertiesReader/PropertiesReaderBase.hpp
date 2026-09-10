#pragma once

#include <algorithm>
#include <filesystem>
#include <fstream>
#include <format>
#include <map>
#include <sstream>
#include <stdexcept>
#include <type_traits>
#include <variant>

template<typename Implementation>
class PropertiesReaderBase
{
protected:
    using DoubleRef = std::reference_wrapper<double>;
    using BoolRef = std::reference_wrapper<bool>;
    using UIntRef = std::reference_wrapper<uint32_t>;
    using Var = std::variant<DoubleRef, BoolRef, UIntRef>;
    using PropertiesMap = std::map<std::string, Var>;

    template<typename PropertiesStruct>
    PropertiesMap CreatePropertiesMap(PropertiesStruct& propertiesStruct) const
    {
        return static_cast<const Implementation*>(this)->CreatePropertiesMap_Impl(propertiesStruct);
    }

    template<typename PropertiesStruct>
    PropertiesStruct ParsePropertiesFile(const std::string& filename) const
    {
        PropertiesStruct output;

        PropertiesMap propertiesMap = CreatePropertiesMap(output);
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

    PropertiesReaderBase() = default;

public:

};
