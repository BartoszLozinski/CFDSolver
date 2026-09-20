#pragma once

#include <vector>
#include <optional>

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

        class IIterativeSolver
        {
        protected:
            DenseMatrix matrix;

        public:
            IIterativeSolver(DenseMatrix matrix_) : matrix(matrix_) {};
            virtual ~IIterativeSolver() = default;
            virtual RhsType Solve(const RhsType& rhs, const RhsType& initialFuess) = 0;
        };
    }
}
