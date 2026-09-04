#pragma once

#include "BoundaryConditionBase.hpp"

namespace BoundaryCondition
{
    class Neumann : public BoundaryConditionBase
    {
    protected:
        std::function<double(double, double, double)> function; // spacedx, spacedy, aligned value
        BoundaryIndicies alignedCellsIndicies;
        
    public:
        Neumann(Grid& grid_, BoundaryIndicies boundaryIndicies_, std::function<double(double, double, double)> function_, BoundaryIndicies alignedCellsIndicies_);
        void Apply(const double spaceStep) final override;
    };
};