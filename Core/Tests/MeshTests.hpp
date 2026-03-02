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
