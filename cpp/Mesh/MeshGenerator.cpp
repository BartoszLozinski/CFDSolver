#include "MeshGenerator.hpp"

Mesh MeshGenerator::GenerateMesh(const double dx, const double dy, const uint32_t nx, const uint32_t ny) const
{
    return Mesh{dx, dy, nx, ny};
}

Mesh MeshGenerator::GenerateMesh(const MeshProperties& meshProperties) const
{
    return Mesh{ meshProperties.dx
               , meshProperties.dy
               , meshProperties.nx
               , meshProperties.ny };
}