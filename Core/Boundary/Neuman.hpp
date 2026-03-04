#pragma once

#include "BoundaryCondition.hpp"

namespace Boundary
{
    namespace Neumann
    {
        using namespace Mesh;

        template<typename T>
        class FixedGradient : public BoundaryCondition<FixedGradient<T>, T>
        {
            private:
                Side side;
                T gradient;
                double dx{};
                double dy{};

            public:
                FixedGradient() = delete;
                FixedGradient(const Side side_, const T gradient_, const double dx_, const double dy_)
                    : side(side_), gradient(gradient_), dx(dx_), dy(dy_)
                {}

                ~FixedGradient() = default;

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
                                field(0, j) = field(1, j) - gradient * dx;
                            break;
                        case Right:
                            for (std::size_t j = 1; j < field.InteriorNy(); ++j)
                                field(nx - 1, j) = field(nx - 2, j) + gradient * dx;
                            break;
                        case Bottom:
                            for (std::size_t i = 1; i < field.InteriorNx(); ++i)
                                field(i, ny - 1) = field(i, ny - 2) + gradient * dy;
                            break;
                        case Top:
                            for (std::size_t i = 1; i < field.InteriorNx(); ++i)
                                field(i, 0) = field(i, 1) - gradient * dy;
                            break;
                    }
                }
        };
    };
};