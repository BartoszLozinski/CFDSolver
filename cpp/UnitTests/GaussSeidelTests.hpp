#pragma once

#include "gtest/gtest.h"

#include "MathOperators/LinearAlgebra/GaussSeidel.hpp"
#include "MathOperators/LinearAlgebra/ListOfLists.hpp"
#include "LinearSystemTestData.hpp"

#include <stdexcept>

//Dense matrix

TEST(GaussSeidelTestsDenseMatrix, SolvesLinearSystem)
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

TEST(GaussSeidelTestsDenseMatrix, UsesInitialGuess)
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

TEST(GaussSeidelTestsDenseMatrix, RejectsRhsWithWrongNumberOfRows)
{
    Math::LinearAlgebra::GaussSeidel solver{
        {{1.0, 0.0}, {0.0, 1.0}}};

    EXPECT_THROW(
        solver.Solve({1.0}, {0.0, 0.0}),
        std::invalid_argument);
}

TEST(GaussSeidelTestsDenseMatrix, RejectsInitialGuessWithWrongNumberOfRows)
{
    Math::LinearAlgebra::GaussSeidel solver{
        {{1.0, 0.0}, {0.0, 1.0}}};

    EXPECT_THROW(
        solver.Solve({1.0, 1.0}, {0.0}),
        std::invalid_argument);
}

TEST(GaussSeidelTestsDenseMatrix, RejectsNonSquareMatrix)
{
    const Math::LinearAlgebra::DenseMatrix matrix{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}};

    EXPECT_THROW(
        Math::LinearAlgebra::GaussSeidel solver{matrix},
        std::invalid_argument);
}

// Sparse matrix

TEST(GaussSeidelTestsSparseMatrix, SolvesLinearSystem)
{
    Math::LinearAlgebra::GaussSeidel solver{
        LinearSystemTestData::matrix,
        1e-10,
        1'000};

    const auto lilMatrix = SparseMatrix::GetLilSparseMatrix(LinearSystemTestData::matrix);

    const auto result = solver.Solve(
        lilMatrix,
        LinearSystemTestData::rhs,
        Math::LinearAlgebra::RhsType(LinearSystemTestData::rhs.size(), 0.0));

    ASSERT_EQ(result.size(), LinearSystemTestData::solution.size());
    for (std::size_t index = 0; index < result.size(); ++index)
        EXPECT_NEAR(result[index], LinearSystemTestData::solution[index], 1e-8);
}

TEST(GaussSeidelTestsSparseMatrix, UsesInitialGuess)
{
    Math::LinearAlgebra::GaussSeidel solver{
        LinearSystemTestData::matrix,
        1e-10,
        1'000};

    const auto lilMatrix = SparseMatrix::GetLilSparseMatrix(LinearSystemTestData::matrix);

    const auto result = solver.Solve(
        lilMatrix,
        LinearSystemTestData::secondRhs,
        LinearSystemTestData::solution);

    ASSERT_EQ(result.size(), LinearSystemTestData::secondSolution.size());
    for (std::size_t index = 0; index < result.size(); ++index)
        EXPECT_NEAR(result[index], LinearSystemTestData::secondSolution[index], 1e-8);
}

TEST(GaussSeidelTestsSparseMatrix, RejectsRhsWithWrongNumberOfRows)
{
    const Math::LinearAlgebra::DenseMatrix matrix{{1.0, 0.0}, {0.0, 1.0}};
    Math::LinearAlgebra::GaussSeidel solver{ matrix };
    const auto lilMatrix = SparseMatrix::GetLilSparseMatrix({{1.0, 0.0}, {0.0, 1.0}});

    EXPECT_THROW(
        solver.Solve(lilMatrix, {1.0}, {0.0, 0.0}),
        std::invalid_argument);
}

TEST(GaussSeidelTestsSparseMatrix, RejectsInitialGuessWithWrongNumberOfRows)
{
    const Math::LinearAlgebra::DenseMatrix matrix{{1.0, 0.0}, {0.0, 1.0}};
    Math::LinearAlgebra::GaussSeidel solver{matrix};
    const auto lilMatrix = SparseMatrix::GetLilSparseMatrix(matrix);

    EXPECT_THROW(
        solver.Solve(lilMatrix, {1.0, 1.0}, {0.0}),
        std::invalid_argument);
}
/*
// TODO - add when class moved to use sparse matrix only
TEST(GaussSeidelTestsSparseMatrix, RejectsNonSquareMatrix)
{
    const Math::LinearAlgebra::DenseMatrix matrix{
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}};


    EXPECT_THROW(
        Math::LinearAlgebra::GaussSeidel solver{matrix},
        std::invalid_argument);
}
*/