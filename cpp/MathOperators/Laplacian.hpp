#pragma once

#include <vector>

using Grid2D = std::vector<std::vector<double>>;

namespace Operators
{
    // right now assume uniform grid
    // will be updated for unstructured mesh
    class Laplacian
    {
    private:
        double dx{};
        double dy{};
        const Grid2D& grid;

    public:
        Laplacian(const double dx_, const double dy_, const Grid2D& grid_);
        double operator()(const std::size_t ix, const std::size_t iy) const;
    };
}