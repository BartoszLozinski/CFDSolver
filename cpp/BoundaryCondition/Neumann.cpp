#include "Neumann.hpp"

namespace BoundaryCondition
{
        Neumann::Neumann(Grid& grid_, BoundaryIndicies boundaryCells_, std::function<double(double, double, double)> function_, BoundaryIndicies alignedCellsIndicies_)
            : BoundaryConditionBase(grid_, boundaryCells_)
            , function(function_)
            , alignedCellsIndicies(alignedCellsIndicies_)
        {};

    void Neumann::Apply(const double spaceStep)
    {
        // for simplicity it assumes perfectly structured mesh
        // will be updated to use geometrical mesh properties (cell position)
        //for (size_t i = 0; i < boundaryCells.size(); ++i)
        //    boundaryCells[i] = function(i * spaceStep, alignedCells[i]);
        
        /*
        for (std::size_t rowId = boundaryIndicies.rowStart; rowId < boundaryIndicies.rowEnd; ++rowId)
        {
            for (std::size_t columnId = boundaryIndicies.colStart; columnId < boundaryIndicies.colEnd; ++columnId)
            {
                grid[rowId][columnId] = function(rowId * spaceStep, columnId * spaceStep);
            }
        }*/

        for (std::size_t i = 0; i < boundaryIndicies.size(); ++i)
        {
            auto& cellId = boundaryIndicies.at(i);
            auto& alignedCellId = alignedCellsIndicies.at(i);

            grid[cellId.row][cellId.col] = function( cellId.row * spaceStep
                                                   , cellId.col * spaceStep
                                                   , grid[alignedCellId.row][alignedCellId.col]);
        }
    };
};