#pragma once

#include "BoundaryConditionBase.hpp"

namespace BoundaryCondition
{
    class Neumann : public BoundaryConditionBase
    {
    protected:
        std::function<double(double, double)> function; // spacedx, aligned value
        Cells& alignedCells;
        
    public:
        Neumann(Cells& boundaryCells_, std::function<double(double, double)> function_, Cells& alignedCells_);
        void Apply(const double spaceStep) final override;
    };
};