#pragma once

#include <string>
#include <string_view>
#include <vector>
#include <fstream>

class CSVExporter
{
private:
    void WriteRow(const std::vector<double>& row, std::ofstream& outputFile);
    
public:
    void Export(std::string_view filename, const std::vector<std::vector<double>>& data);
};