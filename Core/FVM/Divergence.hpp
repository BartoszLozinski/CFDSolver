#pragma once

#include "VectorNt.hpp"
#include "Mesh/Field.hpp"

namespace FVM
{
    double Divergence( const Mesh::Field<Vector2d>& velocityField
                     , const std::size_t i
                     , const std::size_t j
                     , const double dx
                     , const double dy);

};