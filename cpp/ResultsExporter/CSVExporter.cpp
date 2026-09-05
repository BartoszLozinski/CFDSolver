#include "CSVExporter.hpp"

#include <filesystem>


void CSVExporter::WriteRow(const std::vector<double>& row, std::ofstream& outputFile)
{
    if (!outputFile.is_open())
        throw std::runtime_error("File is not opened");

    for (const auto& value : row)
    {
        char separator = ',';

        if (value == row.back())
            separator = '\n';

        outputFile << value << separator;
    }
}

void CSVExporter::Export(std::string_view filename, const std::vector<std::vector<double>>& data)
{
    std::filesystem::path path = filename.data();
    std::filesystem::create_directories(path.parent_path());

    std::ofstream outputFile{ path };

    if (!outputFile.is_open())
        throw std::runtime_error("Failed to open file for writing: " + std::string(filename.begin(), filename.end()));

    for (const auto& row : data)
        WriteRow(row, outputFile);

    outputFile.close();
}
