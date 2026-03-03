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

    std::size_t StructuredMesh::Nx() const noexcept { return nx; }
    std::size_t StructuredMesh::Ny() const noexcept { return ny; }
    double StructuredMesh::Lx() const noexcept { return lx; }
    double StructuredMesh::Ly() const noexcept { return ly; }
    double StructuredMesh::Dx() const noexcept { return dx; }
    double StructuredMesh::Dy() const noexcept { return dy; }
    std::size_t StructuredMesh::NumberOfCells() const noexcept { return nx * ny; }
    double StructuredMesh::CellVolume() const noexcept { return dx * dy; }

    //i - cell index in x direction; j - cell index in y direction
    std::size_t StructuredMesh::CellId(const std::size_t i, const std::size_t j) const noexcept
    {
        return i + j * nx;
    }

    std::pair<std::size_t, std::size_t> StructuredMesh::CellIndices(const std::size_t cellId) const noexcept
    {
        return { cellId % nx, cellId / nx };
    }

    bool StructuredMesh::HasNeighbor(const std::size_t i, const std::size_t j, const Direction direction) const noexcept
    {
        using enum Direction;
        switch (direction)
        {
            case Left: return i > 0;
            case Right: return i < nx - 1;
            case Bottom: return j < ny - 1;
            case Top: return j > 0;
            default: return false;
        }
    }

    std::size_t StructuredMesh::NeighborId(const std::size_t i, const std::size_t j, const Direction direction) const noexcept
    {
        using enum Direction;
        switch (direction)
        {
            case Left: return CellId(i - 1, j);
            case Right: return CellId(i + 1, j);
            case Bottom: return CellId(i, j + 1);
            case Top: return CellId(i, j - 1);
        }
    }

    double StructuredMesh::X(const std::size_t i) const noexcept
    {
        return (static_cast<double>(i) + 0.5) * dx;
    };

    double StructuredMesh::Y(const std::size_t j) const noexcept
    {
        return ly - (static_cast<double>(j) + 0.5) * dy;
    };
}