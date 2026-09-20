#include "GaussSeidel.hpp"

#include <algorithm>
#include <limits>
#include <ranges>
#include <stdexcept>

namespace Math
{
    namespace LinearAlgebra
    {
        GaussSeidel::GaussSeidel(DenseMatrix matrix_, const double tolerance_ /* = 1e-6 */, const std::size_t maxIterations_ /* = 10 */)
            : IIterativeSolver(matrix_)
            , tolerance(tolerance_)
            , maxIterations(maxIterations_)
        {
            ValidateMatrix();
        };

        double GaussSeidel::CalculateResidual(const RhsType& solution, const RhsType& rhs) const
        {
            double maxResidual = 0.0;
            for (std::size_t row = 0; row < matrix.size(); ++row)
            {
                double calculatedValue = 0.0;

                //Probably I should add Dot product function
                for (std::size_t column = 0; column < matrix.size(); ++column)
                    calculatedValue += matrix[row][column] * solution[column];

                if (const auto currentResidual = std::abs(calculatedValue - rhs[row]); currentResidual > maxResidual)
                    maxResidual = currentResidual;
            }

            return maxResidual;
        }


        void GaussSeidel::ValidateMatrix() const
        {
            if (std::ranges::any_of(matrix, [&](const auto& row){
                return row.size() != matrix.size(); 
            }))
            {
                throw std::invalid_argument("Matrix needs to be square!");
            }
        }

        void GaussSeidel::ValidateRhs(const RhsType& rhs) const
        {
            if (matrix.size() != rhs.size())
                throw std::invalid_argument("Matrix rows needs to match RHS size!");
        }

        RhsType GaussSeidel::Solve(const RhsType& rhs, const RhsType& initialGuess)
        {
            ValidateRhs(rhs);
            ValidateRhs(initialGuess);
            auto solution = initialGuess; //initial guess with 0

            std::size_t iteration = 0;

            while (iteration < maxIterations && CalculateResidual(solution, rhs) > tolerance)
            {
                for (std::size_t row = 0; row < matrix.size(); ++row)
                {
                    double value = rhs[row];

                    for (std::size_t column = 0; column < matrix.size(); ++column)
                    {
                        if ((column != row))
                            value -= matrix[row][column] * solution[column];
                    }

                    solution[row] = value / matrix[row][row];
                }

                ++iteration;
            }

            return solution;
        }
    }
}