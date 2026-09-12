#include "Laplacian.hpp"

#include <cmath>
#include <format>
#include <stdexcept>

namespace Operators
{
    Laplacian::Laplacian(const double dx_, const double dy_, Grid2D& grid_)
        : dx(dx_)
        , dy(dy_)
        , grid(grid_)
    {
        static constexpr double epsilon = 1e-9;
        if (std::abs(dx) < epsilon or std::abs(dy) < epsilon)
            throw std::invalid_argument(std::format("absolute value of dx {} or dy {} is smaller then allowed {}.", dx, dy, epsilon));
    }

    double Laplacian::operator()(const std::size_t ix, const std::size_t iy) const
    {
        if (ix < 1 || iy < 1 || (ix >= grid.size() - 1) || (iy >= grid.at(0).size() - 1))
            throw std::out_of_range(std::format("Index ix {} or iy {} is out of grid range", ix, iy));

        return (grid[ix + 1][iy] - 2 * grid[ix][iy] + grid[ix - 1][iy]) / (dx * dx) +
               (grid[ix][iy + 1] - 2 * grid[ix][iy] + grid[ix][iy - 1]) / (dy * dy);
    }
}