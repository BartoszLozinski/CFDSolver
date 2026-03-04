#pragma once

#include <cstddef>
#include <utility>

namespace Mesh
{
    // i - increases in x (right) direction (column index); j - increases in y (down) direction (row index)
    enum class Direction
    {
        Left,
        Right,
        Bottom,
        Top,
    };

    class StructuredMesh
    {
    private:
        std::size_t nx{};
        std::size_t ny{};   
        double lx{};
        double ly{};
        double dx{};
        double dy{};
        
    public:
        StructuredMesh() = delete;
        StructuredMesh(const std::size_t nx_, const std::size_t ny_, const double lx_, const double ly_);
        ~StructuredMesh() = default;

        [[nodiscard]] std::size_t Nx() const noexcept;
        [[nodiscard]] std::size_t Ny() const noexcept;
        [[nodiscard]] double Lx() const noexcept;
        [[nodiscard]] double Ly() const noexcept;
        [[nodiscard]] double Dx() const noexcept;
        [[nodiscard]] double Dy() const noexcept;
        [[nodiscard]] std::size_t NumberOfCells() const noexcept;
        [[nodiscard]] double CellVolume() const noexcept;
        [[nodiscard]] std::size_t CellId(const std::size_t i, const std::size_t j) const noexcept;
        [[nodiscard]] std::pair<std::size_t, std::size_t> CellIndices(const std::size_t cellId) const noexcept;
        [[nodiscard]] bool HasNeighbor(const std::size_t i, const std::size_t j, const Direction direction) const noexcept;
        [[nodiscard]] std::size_t NeighborId(const std::size_t i, const std::size_t j, const Direction direction) const noexcept;
        [[nodiscard]] double X(const std::size_t i) const noexcept;
        [[nodiscard]] double Y(const std::size_t j) const noexcept;
    };
};
