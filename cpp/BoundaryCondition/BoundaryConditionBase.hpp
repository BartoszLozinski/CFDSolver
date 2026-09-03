#pragma once

#include <functional>
#include <vector>

using Cells = std::vector<double>;

namespace BoundaryCondition
{
    //double for now. Will be templated when added flow fields (velocity)
    class BoundaryConditionBase
    {
    protected:
        Cells& boundaryCells;
        // for now assume that the function takes only space step for 1 direction
        // will be updated to cell position later
        BoundaryConditionBase(Cells& boundaryCells_);

    public:
        // for now for perfectly structured mesh. will be updated later
        // assuming dx = dy
        virtual void Apply(const double spaceStep) = 0;
        virtual ~BoundaryConditionBase() = default;
    };
};