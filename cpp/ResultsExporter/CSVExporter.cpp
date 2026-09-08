#include "CSVExporter.hpp"

#include <filesystem>


void CSVExporter::WriteRow(const std::vector<double>& row, std::ofstream& outputFile)
{
    for (std::size_t i = 0; i < row.size(); ++i)
    {
        const char separator = (i + 1) != row.size() ? '\t' : '\n';
        outputFile << row[i] << separator;
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
