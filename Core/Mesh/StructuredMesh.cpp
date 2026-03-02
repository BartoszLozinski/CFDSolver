#include "StructuredMesh.hpp"

#include <stdexcept>

namespace Mesh
{
    StructuredMesh::StructuredMesh(const std::size_t nx_, const std::size_t ny_, const double lx_, const double ly_)
        : nx(nx_), ny(ny_), lx(lx_), ly(ly_)
    {
        if (nx == 0 || ny == 0)
            throw std::invalid_argument("Number of cells in each direction must be greater than zero.");
        if (lx <= 0.0 || ly <= 0.0)
            throw std::invalid_argument("Domain lengths must be greater than zero.");

        dx = lx / nx;
        dy = ly / ny;
    }

    bool StructuredMesh::Validate() const noexcept
    {
        if (nx == 0)
            return false;
        if (ny == 0)
            return false;
        if (lx <= 0.0)
            return false;
        if (ly <= 0.0)
            return false;
        
        return true;
    }

    std::size_t StructuredMesh::Nx() const noexcept { return nx; }
    std::size_t StructuredMesh::Ny() const noexcept { return ny; }
    double StructuredMesh::Lx() const noexcept { return lx; }
    double StructuredMesh::Ly() const noexcept { return ly; }
    double StructuredMesh::Dx() const noexcept { return dx; }
    double StructuredMesh::Dy() const noexcept { return dy; }
    std::size_t StructuredMesh::NumberOfCells() const noexcept { return nx * ny; }
    double StructuredMesh::CellVolume() const noexcept { return dx * dy; }
};