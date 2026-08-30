#pragma once

#include <cstdint>
#include "Mesh.hpp"

class MeshGenerator
{
public:
    Mesh GenerateMesh(const double dx, const double dy, const uint32_t nx, const uint32_t ny) const;
};
