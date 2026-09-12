#pragma once

#include "gtest/gtest.h"

#include "MathOperators/Laplacian.hpp"

#include <vector>

TEST(LaplacianTests, LinearFieldHasZeroLaplacian)
{
    Grid2D grid(5, std::vector<double>(5, 0.0));
    for (std::size_t i = 0; i < grid.size(); ++i)
    {
        for (std::size_t j = 0; j < grid[i].size(); ++j)
        {
            grid[i][j] = static_cast<double>(i) + static_cast<double>(j);
        }
    }

    Operators::Laplacian laplacian{1.0, 1.0, grid};

    EXPECT_DOUBLE_EQ(laplacian(2, 2), 0.0);
}

TEST(LaplacianTests, OutOfRangeIndexThrows)
{
    Grid2D grid(5, std::vector<double>(5, 0.0));
    Operators::Laplacian laplacian{1.0, 1.0, grid};

    EXPECT_THROW(laplacian(0, 2), std::out_of_range);
    EXPECT_THROW(laplacian(2, 0), std::out_of_range);
    EXPECT_THROW(laplacian(4, 2), std::out_of_range);
    EXPECT_THROW(laplacian(2, 4), std::out_of_range);
}

TEST(LaplacianTests, ZeroSpacingThrows)
{
    Grid2D grid(5, std::vector<double>(5, 0.0));

    EXPECT_THROW((Operators::Laplacian{0.0, 1.0, grid}), std::invalid_argument);
    EXPECT_THROW((Operators::Laplacian{1.0, 0.0, grid}), std::invalid_argument);
}

TEST(LaplacianTests, ComputesExactStencilValue)
{
    Grid2D grid(5, std::vector<double>(5, 0.0));
    grid[1][1] = 0.0;
    grid[0][1] = 1.0;
    grid[2][1] = 3.0;
    grid[1][0] = 2.0;
    grid[1][2] = 4.0;

    static constexpr double dx = 1.0;
    static constexpr double dy = 1.0;
    Operators::Laplacian laplacian{dx, dy, grid};

    const double expected =
        (3.0 - 2.0 * 0.0 + 1.0) / (dx * dx) +
        (4.0 - 2.0 * 0.0 + 2.0) / (dy * dy);

    EXPECT_DOUBLE_EQ(laplacian(1, 1), expected);
}
