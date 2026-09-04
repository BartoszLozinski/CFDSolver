#pragma once

#include <functional>
#include <vector>

struct CellID
{
    std::size_t row{};
    std::size_t col{};
};

using Grid = std::vector<std::vector<double>>;
using BoundaryIndicies = std::vector<CellID>;


namespace BoundaryCondition
{
    //double for now. Will be templated when added flow fields (velocity)
    class BoundaryConditionBase
    {
    protected:
        Grid& grid;
        BoundaryIndicies boundaryIndicies;
        // for now assume that the function takes only space step for 1 direction
        // will be updated to cell position later
        BoundaryConditionBase(Grid& grid_, BoundaryIndicies boundaryIndicies_);

    public:
        // for now for perfectly structured mesh. will be updated later
        // assuming dx = dy
        virtual void Apply(const double spaceStep) = 0;
        virtual ~BoundaryConditionBase() = default;
    };
};