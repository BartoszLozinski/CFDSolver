#pragma once

#include "BoundaryCondition.hpp"

namespace Boundary
{
    using namespace Mesh;

    namespace Direchlet
    {
        template<typename T>
        class FixedValue : public BoundaryCondition<FixedValue<T>, T>
        {
            private:
                Side side;
                T value;

            public:
                FixedValue() = delete;
                FixedValue(const Side side_, const T value_) : side(side_), value(value_) {}
                ~FixedValue() = default;

                void Apply_impl(Mesh::Field<T>& field)
                {
                    const auto nx = field.Nx();
                    const auto ny = field.Ny();

                    using enum Side;
                    switch (side)
                    {
                        //cell-centered FVM grid
                        case Left:
                            for (std::size_t j = 1; j < field.InteriorNy(); ++j)
                                field(0, j) = value * 2- field(1, j);
                            break;
                        case Right:
                            for (std::size_t j = 1; j < field.InteriorNy(); ++j)
                                field(nx - 1, j) = value * 2 - field(nx - 2, j);
                            break;
                        case Bottom:
                            for (std::size_t i = 1; i < field.InteriorNx(); ++i)
                                field(i, ny - 1) = value * 2 - field(i, ny - 2);
                            break;
                        case Top:
                            for (std::size_t i = 1; i < field.InteriorNx(); ++i)
                                field(i, 0) = value * 2 - field(i, 1);
                            break;
                    }
                }
        };
    };
};