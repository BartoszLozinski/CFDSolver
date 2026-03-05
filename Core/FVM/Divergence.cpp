#include "Divergence.hpp"

namespace FVM
{
    double Divergence( const Mesh::Field<Vector2d>& field
                     , const std::size_t i
                     , const std::size_t j
                     , const double dx
                     , const double dy)
    {
        const auto& left = field(i - 1, j);
        const auto& right = field(i + 1, j);
        const auto& top = field(i, j - 1);
        const auto& bottom = field(i, j + 1);

        return (right[0] - left[0]) / (2.0 * dx) + (bottom[1] - top[1]) / (2.0 * dy);
    };
};