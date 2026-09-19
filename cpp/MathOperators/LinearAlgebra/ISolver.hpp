#pragma once

#include <vector>

namespace Math
{
    namespace LinearAlgebra
    {
        using DenseMatrix = std::vector<std::vector<double>>;
        using RhsType = std::vector<double>;

        class ISolver
        {
        protected:
            DenseMatrix matrix;

        public:
            ISolver(DenseMatrix matrix_) : matrix(matrix_) {};
            virtual ~ISolver() = default;
            virtual RhsType Solve(RhsType rhs) = 0;
        };
    }
}
