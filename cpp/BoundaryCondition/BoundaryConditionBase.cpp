#include "BoundaryConditionBase.hpp"

namespace BoundaryCondition
{
    BoundaryConditionBase::BoundaryConditionBase(Grid& grid_, BoundaryIndicies boundaryIndicies_)
        : grid(grid_), boundaryIndicies(boundaryIndicies_)
    {};

};
