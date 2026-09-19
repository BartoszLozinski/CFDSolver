#pragma once

#include "gtest/gtest.h"

#include "MathOperators/LinearAlgebra/GaussElimination.hpp"

#include <stdexcept>
#include <vector>

using Math::LinearAlgebra::DenseMatrix;
TEST(GaussEliminationTests, SolvesLinearSystem)
{
    const DenseMatrix matrix{
        {3.0, 2.0, -1.0},
        {2.0, -2.0, 4.0},
        {-1.0, 0.5, -1.0}
    };
    const std::vector<double> rhs{1.0, -2.0, 0.0};

    Math::LinearAlgebra::GaussElimination solver{matrix};
    const auto solution = solver.Solve(rhs);

    ASSERT_EQ(solution.size(), 3);
    EXPECT_NEAR(solution[0], 1.0, 1e-12);
    EXPECT_NEAR(solution[1], -2.0, 1e-12);
    EXPECT_NEAR(solution[2], -2.0, 1e-12);
}

TEST(GaussEliminationTests, ReusesFactorizationForMultipleRhsVectors)
{
    const DenseMatrix matrix{
        {3.0, 2.0, -1.0},
        {2.0, -2.0, 4.0},
        {-1.0, 0.5, -1.0}
    };

    Math::LinearAlgebra::GaussElimination solver{matrix};

    const auto firstSolution = solver.Solve({1.0, -2.0, 0.0});
    const auto secondSolution = solver.Solve({5.0, 14.0, -4.5});

    EXPECT_NEAR(firstSolution[0], 1.0, 1e-12);
    EXPECT_NEAR(firstSolution[1], -2.0, 1e-12);
    EXPECT_NEAR(firstSolution[2], -2.0, 1e-12);
    EXPECT_NEAR(secondSolution[0], 2.0, 1e-12);
    EXPECT_NEAR(secondSolution[1], 1.0, 1e-12);
    EXPECT_NEAR(secondSolution[2], 3.0, 1e-12);
}

TEST(GaussEliminationTests, SwapsRowsForAZeroDiagonalPivot)
{
    const DenseMatrix matrix{
        {0.0, 2.0},
        {1.0, 3.0}
    };
    const std::vector<double> rhs{4.0, 5.0};

    Math::LinearAlgebra::GaussElimination solver{matrix};
    const auto solution = solver.Solve(rhs);

    ASSERT_EQ(solution.size(), 2);
    EXPECT_NEAR(solution[0], -1.0, 1e-12);
    EXPECT_NEAR(solution[1], 2.0, 1e-12);
}

TEST(GaussEliminationTests, RejectsRhsWithWrongNumberOfRows)
{
    const DenseMatrix matrix{
        {1.0, 0.0},
        {0.0, 1.0}
    };

    Math::LinearAlgebra::GaussElimination solver{matrix};

    EXPECT_THROW(solver.Solve({1.0}), std::invalid_argument);
}

TEST(GaussEliminationTests, RejectsNonSquareMatrix)
{
    const DenseMatrix matrix{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };

    EXPECT_THROW(Math::LinearAlgebra::GaussElimination solver{matrix}, std::invalid_argument);
}

TEST(GaussEliminationTests, RejectsSingularMatrix)
{
    const DenseMatrix matrix{
        {1.0, 2.0},
        {2.0, 4.0}
    };

    EXPECT_THROW(Math::LinearAlgebra::GaussElimination solver{matrix}, std::runtime_error);
}
