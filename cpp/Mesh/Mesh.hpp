#pragma once

#include <cstdint>

// For now I dont need space meshgrid yet, as using structured mesh
// Unit moved to unstructred mesh i will just keep information
// about number of cells, and their size
struct Mesh
{
    double dx{};
    double dy{};
    uint32_t nx{};
    uint32_t ny{};
};