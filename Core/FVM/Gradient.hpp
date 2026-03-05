#pragma once

#include "VectorNt.hpp"
#include "Mesh/Field.hpp"

namespace FVM
{
    Vector2d Gradient( const Mesh::Field<double>& velocityField
                     , const std::size_t i
                     , const std::size_t j
                     , const double dx
                     , const double dy);
};