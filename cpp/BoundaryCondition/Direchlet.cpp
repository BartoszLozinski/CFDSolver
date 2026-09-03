#include "Direchlet.hpp"

namespace BoundaryCondition
    {
        Direchlet::Direchlet(Cells& boundaryCells_, std::function<double(double)> function_)
            : BoundaryConditionBase(boundaryCells_)
            , function(function_)
        {};

    void Direchlet::Apply(const double spaceStep)
    {
        // for simplicity it assumes perfectly structured mesh
        // will be updated to use geometrical mesh properties (cell position)
        for (size_t i = 0; i < boundaryCells.size(); ++i)
            boundaryCells[i] = function(i * spaceStep);
    };
};