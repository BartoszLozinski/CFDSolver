#include "ListOfLists.hpp"

#include <cmath>

namespace SparseMatrix
{
    ListOfLists GetLilSparseMatrix(const DenseMatrix& denseMatrix, const double tolerance /* = 1e-12 */)
    {
        ListOfLists output;

        for (const auto& row : denseMatrix)
        {
            auto& sparseRow = output.emplace_back();

            for (std::size_t column = 0; column < row.size(); ++column)
            {
                const auto value = row[column];
                
                if (std::abs(value) > tolerance)
                    sparseRow.push_back({column, value});
            }
        }

        return output;
    }
}
