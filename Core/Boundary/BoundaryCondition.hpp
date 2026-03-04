#pragma once

#include "Mesh/Field.hpp"

namespace Boundary
{
    enum class Side
    {
        Left,
        Right,
        Bottom,
        Top,
    };

    enum class Type
    {
        Dirichlet,
        Neumann,
    };

    template<typename Derived, typename T>
    class BoundaryCondition
    {
        protected:
        public:
            BoundaryCondition() = default;
            ~BoundaryCondition() = default;

            void Apply(Mesh::Field<T>& field)
            {
                static_cast<Derived*>(this)->Apply_impl(field);
            }
    };

};