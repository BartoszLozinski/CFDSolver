#pragma once

#include <vector>
#include "ISolver.hpp"

namespace Math
{
    namespace LinearAlgebra
    {
        class GaussElimination : public ISolver
        {
        private:
            static constexpr double pivotTolerance = 1e-12;
            DenseMatrix lower;
            DenseMatrix upper;
            std::vector<std::size_t> permutation;

            void ValidateMatrix() const;
            void FactorizeMatrix();
            void ValidateRhs(const RhsType& rhs) const;

        public:
            GaussElimination(DenseMatrix matrix_);

            RhsType Solve(RhsType rhs) override final;

        };
    }
}
