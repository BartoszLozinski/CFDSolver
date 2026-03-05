#pragma once

#include "gtest/gtest.h"
#include <type_traits>
#include "../Mesh/Field.hpp"
#include "../Mesh/StructuredMesh.hpp"
#include "../FVM/VectorNt.hpp"

static_assert(!std::is_default_constructible_v<Mesh::Field<int>>, "Field should not be default-constructible");
static_assert(!std::is_convertible_v<Mesh::StructuredMesh, Mesh::Field<int>>, "Field constructor should be explicit");

using Mesh::StructuredMesh;

TEST(FieldTest, ConstructorInitializesSizes)
{
    StructuredMesh mesh(4, 3, 1.0, 1.0);
    Mesh::Field<int> field(mesh);

    // Total size includes ghost cells (+2 in each direction)
    ASSERT_EQ(field.Nx(), 6);
    ASSERT_EQ(field.Ny(), 5);
    ASSERT_EQ(field.InteriorNx(), 4);
    ASSERT_EQ(field.InteriorNy(), 3);
    ASSERT_EQ(field.Size(), 6 * 5);
}

TEST(FieldTest, AccessByCellId)
{
    StructuredMesh mesh(3, 2, 1.0, 1.0);
    Mesh::Field<int> field(mesh);

    for (std::size_t id = 0; id < field.Size(); ++id)
    {
        field[id] = static_cast<int>(id * 3 + 1);
    }

    for (std::size_t id = 0; id < field.Size(); ++id)
    {
        ASSERT_EQ(field[id], static_cast<int>(id * 3 + 1));
    }
}

TEST(FieldTest, AccessByIndices)
{
    const std::size_t nx = 5;
    const std::size_t ny = 4;
    StructuredMesh mesh{ nx, ny, 1.0, 1.0 };
    Mesh::Field<int> field{ mesh };

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            const auto id = i + j * field.Nx();
            field(i, j) = static_cast<int>(id + 10);
        }
    }

    for (std::size_t j = 1; j <= field.InteriorNy(); ++j)
    {
        for (std::size_t i = 1; i <= field.InteriorNx(); ++i)
        {
            const auto id = i + j * field.Nx();
            ASSERT_EQ(field(i, j), field[id]);
            ASSERT_EQ(field(i, j), static_cast<int>(id + 10));
        }
    }
}

TEST(FieldTest, WorksWithComplexType)
{
    StructuredMesh mesh(3, 3, 1.0, 1.0);
    Mesh::Field<Vector2d> vel(mesh);

    for (std::size_t id = 0; id < vel.Size(); ++id)
    {
        vel[id][0] = static_cast<double>(id) * 0.5;
        vel[id][1] = static_cast<double>(id) * -0.25;
    }

    for (std::size_t j = 0; j < vel.Ny(); ++j)
    {
        for (std::size_t i = 0; i < vel.Nx(); ++i)
        {
            const auto id = i + j * vel.Nx();
            ASSERT_DOUBLE_EQ(vel(i, j)[0], vel[id][0]);
            ASSERT_DOUBLE_EQ(vel(i, j)[1], vel[id][1]);
        }
    }
}
