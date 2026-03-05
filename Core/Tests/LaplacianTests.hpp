#include "../FVM/Laplacian.hpp"
#include <gtest/gtest.h>

TEST(FVMOperators, LaplacianLinearField)
{
    const std::size_t nx = 10;
    const std::size_t ny = 10;
    const double dx = 1.0;
    const double dy = 1.0;

    Mesh::StructuredMesh mesh(nx, ny, dx, dy);
    Mesh::Field<double> field(mesh);

    // φ = x^2 + y^2
    for (std::size_t j = 0; j < field.Ny(); ++j)
    {
        for (std::size_t i = 0; i < field.Nx(); ++i)
        {
            field(i,j) = i * i + j * j;
        }
    }

    auto laplacian = FVM::Laplacian(field, 5, 5, dx, dy);

    EXPECT_NEAR(laplacian, 4.0, 1e-9);
}
