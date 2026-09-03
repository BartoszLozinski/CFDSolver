#include "Neumann.hpp"

namespace BoundaryCondition
    {
        Neumann::Neumann(Cells& boundaryCells_, std::function<double(double, double)> function_, Cells& alignedCells_)
        : BoundaryConditionBase(boundaryCells_)
        , function(function_)
        , alignedCells(alignedCells_)
    {};

    void Neumann::Apply(const double spaceStep)
    {
        // for simplicity it assumes perfectly structured mesh
        // will be updated to use geometrical mesh properties (cell position)
        for (size_t i = 0; i < boundaryCells.size(); ++i)
            boundaryCells[i] = function(i * spaceStep, alignedCells[i]);
    };
};