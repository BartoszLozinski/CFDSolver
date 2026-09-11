#pragma once

#include "gtest/gtest.h"

#include "PropertiesReader/PropertiesReaderBase.hpp"

#include <cstdint>
#include <filesystem>
#include <format>
#include <stdexcept>
#include <tuple>

class FileCreator
{
public:
    std::string filename;

    FileCreator(const std::string& filename_)
        : filename(filename_)
    {};

    void CreateFile(const std::string& doubleValue, const std::string& boolValueStr, const std::string& uint32t_value)
    {
        std::ofstream file{filename};

        if (!file)
            throw std::runtime_error(std::format("Unable to open testing file {}", filename));

        file << "{\n";
        file << std::format("\tdoubleValue\t\t{}\n", doubleValue);
        file << std::format("\tboolValue\t\t{}\n", boolValueStr);
        file << std::format("\tuint32_tValue\t\t{}\n", uint32t_value);
        file << "}\n";        
    }

    void DeleteFile()
    {
        std::filesystem::remove(filename);
    }
};

struct TestProperties
{
    double doubleValue{};
    bool boolValue{false};
    uint32_t uint32_tValue{};
};

class TestPropertiesReader : public PropertiesReaderBase<TestPropertiesReader>
{
friend PropertiesReaderBase<TestPropertiesReader>;

protected:
    PropertiesMap CreatePropertiesMap_Impl(TestProperties& propertiesStruct) const
    {
        return PropertiesMap{
            {"doubleValue", DoubleRef{propertiesStruct.doubleValue}},
            {"boolValue", BoolRef{propertiesStruct.boolValue}},
            {"uint32_tValue", UIntRef{propertiesStruct.uint32_tValue}}
        };
    }
public:
    TestPropertiesReader() = default;
    TestProperties ReadFromSetupFile(const std::string& filename /* = "Setup/MaterialProperties" */) const
    {
        return ParsePropertiesFile<TestProperties>(filename);
    }

};

class TestPropertiesReaderFixture : public testing::TestWithParam<std::tuple<double, std::string, uint32_t, bool>>
{
public:
    TestPropertiesReader reader;
    FileCreator fileCreator{"testFile"};

};

TEST_P(TestPropertiesReaderFixture, ReadingTests)
{
    auto [expectedDouble, expectedBoolStr, expectedUint32t, expectedBool] = GetParam();
    fileCreator.CreateFile(std::to_string(expectedDouble), expectedBoolStr, std::to_string(expectedUint32t));

    auto testProperties = reader.ReadFromSetupFile(fileCreator.filename);

    ASSERT_TRUE(testProperties.doubleValue == expectedDouble);
    ASSERT_TRUE(testProperties.boolValue == expectedBool);
    ASSERT_TRUE(testProperties.uint32_tValue == expectedUint32t);
};

INSTANTIATE_TEST_SUITE_P(ReadingTestsParams, TestPropertiesReaderFixture, testing::Values(
    std::make_tuple(50.0, "true", 100, true),
    std::make_tuple(50.0, "True", 100, true),
    std::make_tuple(50.0, "TRUE", 100, true),
    std::make_tuple(50.0, "false", 100, false),
    std::make_tuple(50.0, "False", 100, false),
    std::make_tuple(50.0, "FALSE", 100, false),
    std::make_tuple(50.0, "invalid", 100, false)
    )
);
