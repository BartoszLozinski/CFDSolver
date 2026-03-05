#pragma once

#include "gtest/gtest.h"
#include "../Mesh/StructuredMesh.hpp"

class InvalidMeshTest : public ::testing::TestWithParam<std::tuple<std::size_t, std::size_t, double, double>>
{};

TEST_P(InvalidMeshTest, ConstructorThrowsInvalidArgument)
{
    const auto [nx, ny, lx, ly] = GetParam();
    EXPECT_THROW(Mesh::StructuredMesh(nx, ny, lx, ly), std::invalid_argument);
}

INSTANTIATE_TEST_SUITE_P(
    InvalidMeshTests,
    InvalidMeshTest,
    ::testing::Values(
        std::make_tuple(0, 10, 1.0, 1.0),
        std::make_tuple(10, 0, 1.0, 1.0),
        std::make_tuple(10, 10, -1.0, 1.0),
        std::make_tuple(10, 10, 1.0, -1.0)
    )
);

TEST(ValidMeshTest, ConstructorCreatesValidMesh)
{
    Mesh::StructuredMesh mesh(10, 10, 1.0, 1.0);
    ASSERT_EQ(mesh.Dx(), 0.1);
    ASSERT_EQ(mesh.Dy(), 0.1);
    ASSERT_EQ(mesh.NumberOfCells(), 100);
    ASSERT_NEAR(mesh.CellVolume(), 0.01, 1e-6);
}

using Mesh::StructuredMesh;
using Mesh::Direction;

TEST(StructuredMeshExtraTest, CellIdAndCellIndicesRoundTrip)
{
    const std::size_t nx = 4;
    const std::size_t ny = 3;
    StructuredMesh mesh(nx, ny, 1.0, 1.0);

    for (std::size_t j = 0; j < ny; ++j)
    {
        for (std::size_t i = 0; i < nx; ++i)
        {
            const auto id = mesh.CellId(i, j);
            const auto idx = mesh.CellIndices(id);
            ASSERT_EQ(idx.first, i);
            ASSERT_EQ(idx.second, j);
        }
    }
}

TEST(StructuredMeshExtraTest, HasNeighborAndNeighborIdLogic)
{
    StructuredMesh mesh(3, 3, 3.0, 3.0);

    ASSERT_TRUE(mesh.HasNeighbor(1, 1, Direction::Left));
    ASSERT_TRUE(mesh.HasNeighbor(1, 1, Direction::Right));
    ASSERT_TRUE(mesh.HasNeighbor(1, 1, Direction::Top));
    ASSERT_TRUE(mesh.HasNeighbor(1, 1, Direction::Bottom));

    ASSERT_EQ(mesh.NeighborId(1, 1, Direction::Left), mesh.CellId(0, 1));
    ASSERT_EQ(mesh.NeighborId(1, 1, Direction::Right), mesh.CellId(2, 1));
    ASSERT_EQ(mesh.NeighborId(1, 1, Direction::Top), mesh.CellId(1, 0));
    ASSERT_EQ(mesh.NeighborId(1, 1, Direction::Bottom), mesh.CellId(1, 2));

    ASSERT_FALSE(mesh.HasNeighbor(0, 0, Direction::Left));
    ASSERT_FALSE(mesh.HasNeighbor(0, 0, Direction::Top));
    ASSERT_TRUE(mesh.HasNeighbor(0, 0, Direction::Right));
    ASSERT_TRUE(mesh.HasNeighbor(0, 0, Direction::Bottom));
}

TEST(StructuredMeshExtraTest, CoordinatesAreCellCenters)
{
    const double Lx = 2.0;
    const double Ly = 1.0;
    const std::size_t nx = 4;
    const std::size_t ny = 2;
    StructuredMesh mesh(nx, ny, Lx, Ly);

    const double dx = mesh.Dx();
    const double dy = mesh.Dy();

    for (std::size_t i = 0; i < nx; ++i)
    {
        const double expectedX = (static_cast<double>(i) + 0.5) * dx;
        ASSERT_NEAR(mesh.X(i), expectedX, 1e-12);
    }

    for (std::size_t j = 0; j < ny; ++j)
    {
        const double expectedY = Ly - (static_cast<double>(j) + 0.5) * dy;
        ASSERT_NEAR(mesh.Y(j), expectedY, 1e-12);
    }
}
