#include "../FVM/Gradient.hpp"
#include <gtest/gtest.h>

TEST(FVMOperators, GradientLinearField)
{
    const std::size_t nx = 10;
    const std::size_t ny = 10;
    const double dx = 1.0;
    const double dy = 1.0;

    Mesh::StructuredMesh mesh(nx, ny, dx, dy);
    Mesh::Field<double> field(mesh);

    // φ = 2x + 3y
    for (std::size_t j = 0; j < field.Ny(); ++j)
    {
        for (std::size_t i = 0; i < field.Nx(); ++i)
        {
            field(i,j) = 2.0 * i + 3.0 * j;
        }
    }

    auto grad = FVM::Gradient(field, 5, 5, dx, dy);

    EXPECT_NEAR(grad[0], 2.0, 1e-9);
    EXPECT_NEAR(grad[1], 3.0, 1e-9);
}
