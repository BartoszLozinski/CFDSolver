#pragma once

#include "gtest/gtest.h"
#include "../Mesh/Field.hpp"
#include "../Mesh/StructuredMesh.hpp"
#include "../Boundary/BoundaryCondition.hpp"
#include "../Boundary/Direchlet.hpp"
#include "../Boundary/Neuman.hpp"

using Mesh::StructuredMesh;
using Mesh::Field;
using Mesh::Velocity;
using Boundary::Side;
using Boundary::Direchlet::FixedValue;
using Boundary::Neumann::FixedGradient;

// ============================================================================
// Dirichlet BC Tests (FixedValue)
// ============================================================================

TEST(DirichletBCTest, FixedValueLeftSide)
{
    StructuredMesh mesh(4, 3, 1.0, 1.0);
    Field<double> field(mesh);

    // Initialize interior cells
    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = static_cast<double>(i + j);
        }
    }

    // Apply Dirichlet BC on left side with value = 10.0
    FixedValue<double> bc_left(Side::Left, 10.0);
    bc_left.Apply(field);

    // Verify: ghost cell = 2 * value - interior_cell
    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        const double expected = 2 * 10.0 - field(1, j);
        ASSERT_DOUBLE_EQ(field(0, j), expected);
    }
}

TEST(DirichletBCTest, FixedValueRightSide)
{
    StructuredMesh mesh(4, 3, 1.0, 1.0);
    Field<double> field(mesh);

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = static_cast<double>(i * j);
        }
    }

    FixedValue<double> bc_right(Side::Right, 5.0);
    bc_right.Apply(field);

    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        const std::size_t nx = field.Nx();
        const double expected = 2 * 5.0 - field(nx - 2, j);
        ASSERT_DOUBLE_EQ(field(nx - 1, j), expected);
    }
}

TEST(DirichletBCTest, FixedValueTopSide)
{
    StructuredMesh mesh(3, 4, 1.0, 1.0);
    Field<double> field(mesh);

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = static_cast<double>(i + 2 * j);
        }
    }

    FixedValue<double> bc_top(Side::Top, 3.0);
    bc_top.Apply(field);

    for (std::size_t i = 1; i < field.InteriorNx(); ++i)
    {
        const double expected = 2 * 3.0 - field(i, 1);
        ASSERT_DOUBLE_EQ(field(i, 0), expected);
    }
}

TEST(DirichletBCTest, FixedValueBottomSide)
{
    StructuredMesh mesh(3, 4, 1.0, 1.0);
    Field<double> field(mesh);
    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = static_cast<double>(i - j);
        }
    }

    FixedValue<double> bc_bottom(Side::Bottom, 7.0);
    bc_bottom.Apply(field);

    for (std::size_t i = 1; i < field.InteriorNx(); ++i)
    {
        const std::size_t ny = field.Ny();
        const double expected = 2 * 7.0 - field(i, ny - 2);
        ASSERT_DOUBLE_EQ(field(i, ny - 1), expected);
    }
}

TEST(DirichletBCTest, FixedValueWithVelocity)
{
    StructuredMesh mesh(3, 3, 1.0, 1.0);
    Field<Velocity> field(mesh);

    // Initialize interior cells
    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j).u = static_cast<double>(i);
            field(i, j).v = static_cast<double>(j);
        }
    }

    Velocity bc_value{2.0, 3.0};
    FixedValue<Velocity> bc_left(Side::Left, bc_value);
    bc_left.Apply(field);

    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        ASSERT_DOUBLE_EQ(field(0, j).u, 2 * 2.0 - field(1, j).u);
        ASSERT_DOUBLE_EQ(field(0, j).v, 2 * 3.0 - field(1, j).v);
    }
}

// ============================================================================
// Neumann BC Tests (FixedGradient)
// ============================================================================

TEST(NeumannBCTest, FixedGradientLeftSide)
{
    StructuredMesh mesh(4, 3, 1.0, 1.0);
    Field<double> field(mesh);
    const double dx = mesh.Dx();
    const double dy = mesh.Dy();

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = 100.0;
        }
    }

    const double gradient = 5.0;
    FixedGradient<double> bc_left(Side::Left, gradient, dx, dy);
    bc_left.Apply(field);

    // Verify: ghost = interior - gradient * dx
    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        const double expected = field(1, j) - gradient * dx;
        ASSERT_DOUBLE_EQ(field(0, j), expected);
    }
}

TEST(NeumannBCTest, FixedGradientRightSide)
{
    StructuredMesh mesh(4, 3, 1.0, 1.0);
    Field<double> field(mesh);
    const double dx = mesh.Dx();
    const double dy = mesh.Dy();
    
    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = 50.0;
        }
    }

    const double gradient = 2.0;
    FixedGradient<double> bc_right(Side::Right, gradient, dx, dy);
    bc_right.Apply(field);

    // Verify: ghost = interior + gradient * dx
    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        const std::size_t nx = field.Nx();
        const double expected = field(nx - 2, j) + gradient * dx;
        ASSERT_DOUBLE_EQ(field(nx - 1, j), expected);
    }
}

TEST(NeumannBCTest, FixedGradientTopSide)
{
    StructuredMesh mesh(3, 4, 1.0, 1.0);
    Field<double> field(mesh);
    const double dx = mesh.Dx();
    const double dy = mesh.Dy();

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = 75.0;
        }
    }

    const double gradient = 3.0;
    FixedGradient<double> bc_top(Side::Top, gradient, dx, dy);
    bc_top.Apply(field);

    // Verify: ghost = interior - gradient * dy
    for (std::size_t i = 1; i < field.InteriorNx(); ++i)
    {
        const double expected = field(i, 1) - gradient * dy;
        ASSERT_DOUBLE_EQ(field(i, 0), expected);
    }
}

TEST(NeumannBCTest, FixedGradientBottomSide)
{
    StructuredMesh mesh(3, 4, 1.0, 1.0);
    Field<double> field(mesh);
    const double dx = mesh.Dx();
    const double dy = mesh.Dy();

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = 25.0;
        }
    }

    const double gradient = 1.5;
    FixedGradient<double> bc_bottom(Side::Bottom, gradient, dx, dy);
    bc_bottom.Apply(field);

    // Verify: ghost = interior + gradient * dy
    for (std::size_t i = 1; i < field.InteriorNx(); ++i)
    {
        const std::size_t ny = field.Ny();
        const double expected = field(i, ny - 2) + gradient * dy;
        ASSERT_DOUBLE_EQ(field(i, ny - 1), expected);
    }
}

TEST(NeumannBCTest, FixedGradientWithVelocity)
{
    StructuredMesh mesh(3, 3, 1.0, 1.0);
    Field<Velocity> field(mesh);
    const double dx = mesh.Dx();
    const double dy = mesh.Dy();

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j).u = 10.0;
            field(i, j).v = 20.0;
        }
    }

    Velocity gradient_val{1.0, 2.0};
    FixedGradient<Velocity> bc_left(Side::Left, gradient_val, dx, dy);
    bc_left.Apply(field);

    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        ASSERT_DOUBLE_EQ(field(0, j).u, field(1, j).u - gradient_val.u * dx);
        ASSERT_DOUBLE_EQ(field(0, j).v, field(1, j).v - gradient_val.v * dx);
    }
}

TEST(NeumannBCTest, ZeroGradient)
{
    StructuredMesh mesh(3, 3, 1.0, 1.0);
    Field<double> field(mesh);
    const double dx = mesh.Dx();
    const double dy = mesh.Dy();

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = 42.0;
        }
    }

    // Zero gradient should copy boundary value from interior
    FixedGradient<double> bc_left(Side::Left, 0.0, dx, dy);
    bc_left.Apply(field);

    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        ASSERT_DOUBLE_EQ(field(0, j), field(1, j));
    }
}

// ============================================================================
// Edge cases and combined tests
// ============================================================================

TEST(BoundaryConditionTest, NegativeGradient)
{
    StructuredMesh mesh(3, 3, 1.0, 1.0);
    Field<double> field(mesh);
    const double dx = mesh.Dx();
    const double dy = mesh.Dy();

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = 50.0;
        }
    }

    FixedGradient<double> bc_right(Side::Right, -2.0, dx, dy);
    bc_right.Apply(field);

    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        const std::size_t nx = field.Nx();
        const double expected = field(nx - 2, j) + (-2.0) * dx;
        ASSERT_DOUBLE_EQ(field(nx - 1, j), expected);
    }
}

TEST(BoundaryConditionTest, LargeGrid)
{
    StructuredMesh mesh(50, 30, 10.0, 5.0);
    Field<double> field(mesh);

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            field(i, j) = static_cast<double>(i * j);
        }
    }

    FixedValue<double> bc(Side::Left, 100.0);
    bc.Apply(field);

    // Verify all left ghost cells
    for (std::size_t j = 1; j < field.InteriorNy(); ++j)
    {
        const double expected = 2 * 100.0 - field(1, j);
        ASSERT_DOUBLE_EQ(field(0, j), expected);
    }
}
