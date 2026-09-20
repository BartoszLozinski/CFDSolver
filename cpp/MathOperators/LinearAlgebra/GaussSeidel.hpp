#pragma once

#include "ISolver.hpp"
#include "ListOfLists.hpp"

namespace Math
{
    namespace LinearAlgebra
    {
        class GaussSeidel : public IIterativeSolver
        {
        private:
            double tolerance = 1e-6;
            std::size_t maxIterations = 10;
            void ValidateMatrix() const;
            void ValidateRhs(const RhsType& rhs) const;
            double CalculateResidual(const RhsType& solution, const RhsType& rhs) const;

        public:
            GaussSeidel(DenseMatrix matrix_, const double tolerance_ = 1e-6, const std::size_t maxIterations_ = 10);

            RhsType Solve(const RhsType& rhs, const RhsType& initialGuess) override final;
            RhsType Solve(const SparseMatrix::ListOfLists& sparseMatrix, const RhsType& rhs, const RhsType& initialGuess) const;
        };
    }
}
