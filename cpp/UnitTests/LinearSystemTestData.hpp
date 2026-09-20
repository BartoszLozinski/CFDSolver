#pragma once

#include "MathOperators/LinearAlgebra/ISolver.hpp"

namespace LinearSystemTestData
{
    inline const Math::LinearAlgebra::DenseMatrix matrix{
        {4.0, 1.0, 1.0},
        {1.0, 5.0, 1.0},
        {1.0, 1.0, 6.0}
    };

    inline const Math::LinearAlgebra::RhsType rhs{9.0, 14.0, 21.0};
    inline const Math::LinearAlgebra::RhsType solution{1.0, 2.0, 3.0};

    inline const Math::LinearAlgebra::RhsType secondRhs{13.0, 11.0, 27.0};
    inline const Math::LinearAlgebra::RhsType secondSolution{2.0, 1.0, 4.0};
}