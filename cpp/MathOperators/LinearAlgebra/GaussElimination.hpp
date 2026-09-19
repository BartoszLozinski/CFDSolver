#pragma once

#include <vector>

namespace Math
{
    namespace LinearAlgebra
    {
        using DenseMatrix = std::vector<std::vector<double>>;
        
        // for now standalone function
        // will abstract if more solvers are added (i.e Gauss-Seidel)
        std::vector<double> GaussElimination(DenseMatrix matrix, std::vector<double> rhs, const double pivotTolerance = 1e-12);
    }
}
