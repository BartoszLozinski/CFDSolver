#pragma once

#include <cstdint>
#include <vector>

namespace SparseMatrix
{
    struct ListOfListsData
    {
        std::size_t column{};
        double value{};
    };

    using ListOfLists = std::vector<std::vector<ListOfListsData>>;
    using DenseMatrix = std::vector<std::vector<double>>;

    ListOfLists GetLilSparseMatrix(const DenseMatrix& denseMatrix, const double tolerance = 1e-12);
}
