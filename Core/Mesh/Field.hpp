#pragma once

#include <cassert>
#include <vector>

#include "StructuredMesh.hpp"

namespace Mesh
{
    template<typename T>
    class Field
    {
    private:
        std::size_t nx{};           // Total including ghost cells
        std::size_t ny{};           // Total including ghost cells
        std::size_t interior_nx{};  // Original mesh
        std::size_t interior_ny{};  // Original mesh
        std::vector<T> data;
    public:
        
        Field() = delete;
        explicit Field(const StructuredMesh& mesh)
            : nx(mesh.Nx() + 2), ny(mesh.Ny() + 2), 
              interior_nx(mesh.Nx()), interior_ny(mesh.Ny()),
              data((mesh.Nx() + 2) * (mesh.Ny() + 2))
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
        
        std::size_t InteriorNx() const noexcept { return interior_nx; }
        std::size_t InteriorNy() const noexcept { return interior_ny; }

        ~Field() = default;
    };
};