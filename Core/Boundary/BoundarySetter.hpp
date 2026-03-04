#pragma once

#include "BoundaryCondition.hpp"
#include <concepts>
#include <memory>

namespace Boundary
{

    template<typename BC, typename T>
    concept BoundaryConcept = requires(BC bc, Mesh::Field<T>& field, double dx, double dy)
    {
        { bc.Apply(field, dx, dy) } -> std::same_as<void>;
    };

    template<typename T, BoundaryConcept<T> BC>
    struct BoundarySetter
    {
        BC boundaryCondition;

        void Apply(Mesh::Field<T>& field)
        {
            boundaryCondition.Apply(field);
        }
    };
};