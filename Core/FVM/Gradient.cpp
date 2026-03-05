#include "Gradient.hpp"

namespace FVM
{
    Vector2d Gradient( const Mesh::Field<double>& velocityField
                     , const std::size_t i
                     , const std::size_t j
                     , const double dx
                     , const double dy)
    {
        const auto& left = velocityField(i - 1, j);
        const auto& right = velocityField(i + 1, j);
        const auto& top = velocityField(i, j - 1);
        const auto& bottom = velocityField(i, j + 1);

        return { (right - left) / (2.0 * dx), (bottom - top) / (2.0 * dy) };
    };
};