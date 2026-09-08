#pragma once

#include <cstdint>

// Currently for perfectly structured mesh
// To be updated when imported mesh is used
// Its also same structure as Mesh in Mesh library
// however created to inject dependecy for Readers
struct MeshProperties
{
    double dx{};
    double dy{};
    uint32_t nx{};
    uint32_t ny{};
};