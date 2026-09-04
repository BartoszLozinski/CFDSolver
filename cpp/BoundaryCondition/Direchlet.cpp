#include "Direchlet.hpp"

namespace BoundaryCondition
{
    Direchlet::Direchlet(Grid& grid_, BoundaryIndicies boundaryIndicies_, std::function<double(double, double)> function_)
        : BoundaryConditionBase(grid_, boundaryIndicies_)
        , function(function_)
    {};

    void Direchlet::Apply(const double spaceStep)
    {
        // for simplicity it assumes perfectly structured mesh
        // will be updated to use geometrical mesh properties (cell position)

        for (const auto& cellId : boundaryIndicies)
            grid[cellId.row][cellId.col] = function( cellId.row * spaceStep
                                                   , cellId.col * spaceStep);
    };
};