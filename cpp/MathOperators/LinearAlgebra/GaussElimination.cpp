#include "GaussElimination.hpp"

#include <algorithm>
#include <cmath>
#include <ranges>
#include <stdexcept>

namespace Math
{
    namespace LinearAlgebra
    {
        GaussElimination::GaussElimination(DenseMatrix matrix_)
            : ISolver(matrix_)
            , lower(matrix_.size(), std::vector<double>(matrix_.size(), 0.0))
            , upper(std::move(matrix_))
            , permutation(upper.size())
        {
            ValidateMatrix();

            for (std::size_t row = 0; row < permutation.size(); ++row)
            {
                permutation[row] = row;
                lower[row][row] = 1.0;
            }

            FactorizeMatrix();
        };


        void GaussElimination::ValidateMatrix() const
        {
            if (std::ranges::any_of(upper, [&](const auto& row){
                return row.size() != upper.size(); 
            }))
            {
                throw std::invalid_argument("Matrix needs to be square!");
            }
        }

        void GaussElimination::FactorizeMatrix()
        {
            // current diagonal position
            for (std::size_t pivot = 0; pivot < upper.size(); ++pivot)
            {
                // best pivot row
                auto pivotRow = pivot;
                for (std::size_t row = pivot + 1; row < upper.size(); ++row)
                {
                    if (std::abs(upper[row][pivot]) > std::abs(upper[pivotRow][pivot]))
                        pivotRow = row;
                }

                if (std::abs(upper[pivotRow][pivot]) < pivotTolerance)
                    throw std::runtime_error("Matrix is singular");

                std::swap(upper[pivot], upper[pivotRow]); // moving best pivoting row into current pivot row (to be diagonal)
                std::swap(permutation[pivot], permutation[pivotRow]);

                for (std::size_t column = 0; column < pivot; ++column)
                    std::swap(lower[pivot][column], lower[pivotRow][column]);

                // elimination algorithm
                for (std::size_t row = pivot + 1; row < upper.size(); ++row)
                {
                    const auto factor = upper[row][pivot] / upper[pivot][pivot];
                    lower[row][pivot] = factor; // store factor for forward substitution
                    upper[row][pivot] = 0.0;

                    // calculating rest of row elements
                    for (std::size_t column = pivot + 1; column < upper.size(); ++column)
                        upper[row][column] -= factor * upper[pivot][column];
                }
            }
        }

        void GaussElimination::ValidateRhs(const RhsType& rhs) const
        {
            if (upper.size() != rhs.size())
                throw std::invalid_argument("Matrix rows needs to match RHS size!");
        }

        RhsType GaussElimination::Solve(RhsType rhs)
        {
            ValidateRhs(rhs);

            RhsType permutedRhs(rhs.size());
            for (std::size_t row = 0; row < rhs.size(); ++row)
                permutedRhs[row] = rhs[permutation[row]];

            // Forward substitution: solve L * y = P * rhs.
            for (std::size_t pivot = 0; pivot < lower.size(); ++pivot)
            {
                for (std::size_t row = pivot + 1; row < lower.size(); ++row)
                    permutedRhs[row] -= lower[row][pivot] * permutedRhs[pivot];
            }

            // Back substitution: solve U * solution = y.
            RhsType solution(upper.size(), 0.0);
            for (std::size_t row = upper.size(); row-- > 0;)
            {
                // value = rhs[row]
                //       - sum(matrix[row][column] * solution[column])
                //       for column > row

                auto value = permutedRhs[row];
                for (std::size_t column = row + 1; column < upper.size(); ++column)
                    value -= upper[row][column] * solution[column];

                solution[row] = value / upper[row][row];
            }

            return solution;
        }
    }
}
