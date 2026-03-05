#pragma once

#include <vector>
#include "StructuredMesh.hpp"

namespace Mesh
{
    /*
    struct Velocity
    {
        double u{};
        double v{};

        Velocity() = default;
        Velocity(const double u_, const double v_) : u(u_), v(v_) {}
        Velocity(const Velocity& other) : u(other.u), v(other.v) {}
        Velocity(Velocity&& other) noexcept : u(other.u), v(other.v) {}
        ~Velocity() = default;

        Velocity operator=(const Velocity& other) 
        {
            u = other.u;
            v = other.v;
            return *this;
        }

        Velocity operator=(Velocity&& other) noexcept
        {
            u = other.u;
            v = other.v;
            return *this;
        }

        Velocity operator*(const double scalar) const
        {
            return Velocity(u * scalar, v * scalar);
        }

        Velocity operator*(const int scalar) const
        {
            return Velocity(u * scalar, v * scalar);
        }

        Velocity operator/(const double scalar) const
        {
            return Velocity(u / scalar, v / scalar);
        }

        Velocity operator/(const int scalar) const
        {
            return Velocity(u / scalar, v / scalar);
        }

        Velocity operator+(const Velocity& other) const
        {
            return Velocity(u + other.u, v + other.v);
        }

        Velocity operator-(const Velocity& other) const
        {
            return Velocity(u - other.u, v - other.v);
        }

        bool operator==(const Velocity& other) const
        {
            return u == other.u && v == other.v;
        }

        bool operator!=(const Velocity& other) const
        {
            return !(*this == other);
        }


    };*/

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