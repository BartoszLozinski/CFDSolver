#pragma once

#include "gtest/gtest.h"

#include "MathOperators/LinearAlgebra/GaussElimination.hpp"
#include "LinearSystemTestData.hpp"

#include <stdexcept>
TEST(GaussEliminationTests, SolvesLinearSystem)
{
    Math::LinearAlgebra::GaussElimination solver{LinearSystemTestData::matrix};
    const auto result = solver.Solve(LinearSystemTestData::rhs);

    ASSERT_EQ(result.size(), LinearSystemTestData::solution.size());
    for (std::size_t index = 0; index < result.size(); ++index)
        EXPECT_NEAR(result[index], LinearSystemTestData::solution[index], 1e-12);
}

TEST(GaussEliminationTests, ReusesFactorizationForMultipleRhsVectors)
{
    Math::LinearAlgebra::GaussElimination solver{LinearSystemTestData::matrix};

    const auto firstSolution = solver.Solve(LinearSystemTestData::rhs);
    const auto secondSolution = solver.Solve(LinearSystemTestData::secondRhs);

    for (std::size_t index = 0; index < firstSolution.size(); ++index)
        EXPECT_NEAR(firstSolution[index], LinearSystemTestData::solution[index], 1e-12);
    for (std::size_t index = 0; index < secondSolution.size(); ++index)
        EXPECT_NEAR(secondSolution[index], LinearSystemTestData::secondSolution[index], 1e-12);
}

TEST(GaussEliminationTests, SwapsRowsForAZeroDiagonalPivot)
{
    const Math::LinearAlgebra::DenseMatrix matrix{
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
    const Math::LinearAlgebra::DenseMatrix matrix{
        {1.0, 0.0},
        {0.0, 1.0}
    };

    Math::LinearAlgebra::GaussElimination solver{matrix};

    EXPECT_THROW(solver.Solve({1.0}), std::invalid_argument);
}

TEST(GaussEliminationTests, RejectsNonSquareMatrix)
{
    const Math::LinearAlgebra::DenseMatrix matrix{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };

    EXPECT_THROW(Math::LinearAlgebra::GaussElimination solver{matrix}, std::invalid_argument);
}

TEST(GaussEliminationTests, RejectsSingularMatrix)
{
    const Math::LinearAlgebra::DenseMatrix matrix{
        {1.0, 2.0},
        {2.0, 4.0}
    };

    EXPECT_THROW(Math::LinearAlgebra::GaussElimination solver{matrix}, std::runtime_error);
}
