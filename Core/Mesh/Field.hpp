#pragma once

#include <vector>
#include "StructuredMesh.hpp"

namespace Mesh
{
    struct Velocity
    {
        double u{};
        double v{};
    };

    template<typename T>
    class Field
    {
    private:
        std::size_t nx{};
        std::size_t ny{};
        std::vector<T> data;
    public:
        
        Field() = delete;
        explicit Field(const StructuredMesh& mesh)
            : nx(mesh.Nx()), ny(mesh.Ny()), data(mesh.NumberOfCells())
        {}

        T& operator()(const std::size_t i, const std::size_t j)
        {
            assert(i < nx && j < ny);
            return data[i + j * nx];
        }

        const T& operator()(const std::size_t i, const std::size_t j) const
        {
            assert(i < nx && j < ny);
            return data[i + j * nx];
        }

        T& operator[](const std::size_t cellId)
        {
            assert(cellId < data.size());
            return data[cellId];
        }

        const T& operator[](const std::size_t cellId) const
        {
            assert(cellId < data.size());
            return data[cellId];
        }

        std::size_t Nx() const noexcept { return nx; }
        std::size_t Ny() const noexcept { return ny; }
        std::size_t Size() const noexcept { return data.size(); }

        ~Field() = default;
    };
};