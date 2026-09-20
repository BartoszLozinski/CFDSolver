#pragma once

#include "gtest/gtest.h"

#include "MathOperators/LinearAlgebra/GaussSeidel.hpp"
#include "LinearSystemTestData.hpp"

#include <stdexcept>

TEST(GaussSeidelTests, SolvesLinearSystem)
{
    Math::LinearAlgebra::GaussSeidel solver{
        LinearSystemTestData::matrix,
        1e-10,
        1'000};

    const auto result = solver.Solve(
        LinearSystemTestData::rhs,
        Math::LinearAlgebra::RhsType(LinearSystemTestData::rhs.size(), 0.0));

    ASSERT_EQ(result.size(), LinearSystemTestData::solution.size());
    for (std::size_t index = 0; index < result.size(); ++index)
        EXPECT_NEAR(result[index], LinearSystemTestData::solution[index], 1e-8);
}

TEST(GaussSeidelTests, UsesInitialGuess)
{
    Math::LinearAlgebra::GaussSeidel solver{
        LinearSystemTestData::matrix,
        1e-10,
        1'000};

    const auto result = solver.Solve(
        LinearSystemTestData::secondRhs,
        LinearSystemTestData::solution);

    ASSERT_EQ(result.size(), LinearSystemTestData::secondSolution.size());
    for (std::size_t index = 0; index < result.size(); ++index)
        EXPECT_NEAR(result[index], LinearSystemTestData::secondSolution[index], 1e-8);
}

TEST(GaussSeidelTests, RejectsRhsWithWrongNumberOfRows)
{
    Math::LinearAlgebra::GaussSeidel solver{
        {{1.0, 0.0}, {0.0, 1.0}}};

    EXPECT_THROW(
        solver.Solve({1.0}, {0.0, 0.0}),
        std::invalid_argument);
}

TEST(GaussSeidelTests, RejectsInitialGuessWithWrongNumberOfRows)
{
    Math::LinearAlgebra::GaussSeidel solver{
        {{1.0, 0.0}, {0.0, 1.0}}};

    EXPECT_THROW(
        solver.Solve({1.0, 1.0}, {0.0}),
        std::invalid_argument);
}

TEST(GaussSeidelTests, RejectsNonSquareMatrix)
{
    const Math::LinearAlgebra::DenseMatrix matrix{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}};

    EXPECT_THROW(
        Math::LinearAlgebra::GaussSeidel solver{matrix},
        std::invalid_argument);
}