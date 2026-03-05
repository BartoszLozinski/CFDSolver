#pragma once

#include "VectorNt.hpp"
#include "Mesh/Field.hpp"

namespace FVM
{
    double Laplacian( const Mesh::Field<double>& field
                    , const std::size_t i
                    , const std::size_t j
                    , const double dx
                    , const double dy);
}