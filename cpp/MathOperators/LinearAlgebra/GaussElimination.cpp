#include "GaussElimination.hpp"

#include <algorithm>
#include <cmath>
#include <ranges>
#include <stdexcept>

namespace Math
{
    namespace LinearAlgebra
    {
        std::vector<double> GaussElimination(DenseMatrix matrix, std::vector<double> rhs, const double pivotTolerance)
        {
            if (matrix.size() != rhs.size())
                throw std::invalid_argument("Matrix rows needs to match RHS size!");

            if (std::ranges::any_of(matrix, [&](const auto& row){
                return row.size() != matrix.size(); 
            }))
            {
                throw std::invalid_argument("Matrix needs to be square!");
            }

            // TODO - for iterative solver i would use same matrix all the time
            // maybe it should store prepared matrix
            // instead of rearranging it all the time

            // current diagonal position
            for (std::size_t pivot = 0; pivot < rhs.size(); ++pivot)
            {
                //best pivot row
                auto pivotRow = pivot;
                for (std::size_t row = pivot + 1; row < rhs.size(); ++row)
                {
                    if (std::abs(matrix[row][pivot]) > std::abs(matrix[pivotRow][pivot]))
                        pivotRow = row;
                }

                if (std::abs(matrix[pivotRow][pivot]) < pivotTolerance)
                    throw std::runtime_error("Matrix is singular");

                std::swap(matrix[pivot], matrix[pivotRow]); //moving best pivoting row into current pivot row (to be diagonal)
                std::swap(rhs[pivot], rhs[pivotRow]);

                // elimination algorithm
                for (auto row = pivot + 1; row < rhs.size(); ++row)
                {
                    const auto factor = matrix[row][pivot] / matrix[pivot][pivot];
                    matrix[row][pivot] = 0.0; //reduction of numerical noise
                    // mathematically it would be exactly as below, but would have small rounding errors due floating point arithmethics
                    // then loop would start with column = pivot

                    // calculating rest of row elements
                    for (auto column = pivot + 1; column < rhs.size(); ++column)
                        matrix[row][column] -= factor * matrix[pivot][column];

                    rhs[row] -= factor * rhs[pivot];                    
                }
            }

            // back substitution after gauss elimination into upper-triangular
            std::vector<double> solution(rhs.size(), 0.0);
            for (auto row = rhs.size(); row-- > 0;)
            {
                // value = rhs[row]
                //       - sum(matrix[row][column] * solution[column])
                //       for column > row

                auto value = rhs[row];
                for (auto column = row + 1; column < rhs.size(); ++column)
                    value -= matrix[row][column] * solution[column];

                solution[row] = value / matrix[row][row];
            }

            return solution;
        }
    }
}
