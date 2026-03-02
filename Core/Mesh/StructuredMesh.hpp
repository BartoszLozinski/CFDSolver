#pragma once

#include <cstddef>

namespace Mesh
{
    class StructuredMesh
    {
    private:
        std::size_t nx{};
        std::size_t ny{};
        double lx{};
        double ly{};
        double dx{};
        double dy{};

        [[nodiscard]] bool Validate() const noexcept;

    public:
        StructuredMesh() = delete;
        ~StructuredMesh() = default;

        [[nodiscard]] std::size_t Nx() const noexcept;
        [[nodiscard]] std::size_t Ny() const noexcept;
        [[nodiscard]] double Lx() const noexcept;
        [[nodiscard]] double Ly() const noexcept;
        [[nodiscard]] double Dx() const noexcept;
        [[nodiscard]] double Dy() const noexcept;
        [[nodiscard]] std::size_t NumberOfCells() const noexcept;
        [[nodiscard]] double CellVolume() const noexcept;

        StructuredMesh(const std::size_t nx_, const std::size_t ny_, const double lx_, const double ly_);
    };

};
