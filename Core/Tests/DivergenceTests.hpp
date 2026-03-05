#include "../FVM/Divergence.hpp"
#include <gtest/gtest.h>

TEST(FVMOperators, DivergenceLinearField)
{
    const std::size_t nx = 10;
    const std::size_t ny = 10;
    const double dx = 1.0;
    const double dy = 1.0;

    Mesh::StructuredMesh mesh(nx, ny, dx, dy);
    Mesh::Field<Vector2d> field(mesh);

    // φ = 2x + 3y
    for (std::size_t j = 0; j < field.Ny(); ++j)
    {
        for (std::size_t i = 0; i < field.Nx(); ++i)
        {
            field(i,j) = { 2.0 * i, 3.0 * j };
        }
    }

    auto div = FVM::Divergence(field, 5, 5, dx, dy);

    EXPECT_NEAR(div, 5.0, 1e-9);
}
