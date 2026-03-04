#pragma once

#include "gtest/gtest.h"
#include <type_traits>
#include "../Mesh/Field.hpp"
#include "../Mesh/StructuredMesh.hpp"

// Compile-time checks
static_assert(!std::is_default_constructible_v<Mesh::Field<int>>, "Field should not be default-constructible");
static_assert(!std::is_convertible_v<Mesh::StructuredMesh, Mesh::Field<int>>, "Field constructor should be explicit");

using Mesh::StructuredMesh;

TEST(FieldTest, ConstructorInitializesSizes)
{
    StructuredMesh mesh(4, 3, 1.0, 1.0);
    Mesh::Field<int> field(mesh);

    ASSERT_EQ(field.Nx(), mesh.Nx());
    ASSERT_EQ(field.Ny(), mesh.Ny());
    ASSERT_EQ(field.Size(), mesh.NumberOfCells());
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

    for (std::size_t j = 0; j < ny; ++j)
    {
        for (std::size_t i = 0; i < nx; ++i)
        {
            const auto id = mesh.CellId(i, j);
            field(i, j) = static_cast<int>(id + 10);
        }
    }

    for (std::size_t j = 0; j < ny; ++j)
    {
        for (std::size_t i = 0; i < nx; ++i)
        {
            const auto id = mesh.CellId(i, j);
            ASSERT_EQ(field(i, j), field[id]);
            ASSERT_EQ(field(i, j), static_cast<int>(id + 10));
        }
    }
}

TEST(FieldTest, WorksWithComplexType)
{
    StructuredMesh mesh(3, 3, 1.0, 1.0);
    Mesh::Field<Mesh::Velocity> vel(mesh);

    for (std::size_t id = 0; id < vel.Size(); ++id)
    {
        vel[id].u = static_cast<double>(id) * 0.5;
        vel[id].v = static_cast<double>(id) * -0.25;
    }

    for (std::size_t j = 0; j < vel.Ny(); ++j)
    {
        for (std::size_t i = 0; i < vel.Nx(); ++i)
        {
            const auto id = mesh.CellId(i, j);
            ASSERT_DOUBLE_EQ(vel(i, j).u, vel[id].u);
            ASSERT_DOUBLE_EQ(vel(i, j).v, vel[id].v);
        }
    }
}
