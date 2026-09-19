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
            double pivotTolerance = 1e-12;
            void Validate(const DenseMatrix& matrix, const std::vector<double>& rhs) const;

        public:
            GaussElimination(DenseMatrix matrix_);

            RhsType Solve(RhsType rhs) override final;

        };
    }
}
