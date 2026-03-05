#include "Laplacian.hpp"

namespace FVM
{
    double Laplacian( const Mesh::Field<double>& field
                , const std::size_t i
                , const std::size_t j
                , const double dx
                , const double dy)
    {
        const auto& left = field(i - 1, j);
        const auto& right = field(i + 1, j);
        const auto& top = field(i, j - 1);
        const auto& bottom = field(i, j + 1);
        const auto& center = field(i, j);

        return (right - 2.0 * center + left) / (dx * dx) +
               (bottom - 2.0 * center + top) / (dy * dy);

    };

};