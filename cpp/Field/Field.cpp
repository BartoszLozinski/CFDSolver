#include "Field.hpp"

Field::Field(const Mesh& mesh_)
    : mesh(&mesh_)
{
    static constexpr uint32_t ghostCellOffset = 2;
    static constexpr double defualtValue = 0.0;

    grid.resize(mesh->nx + ghostCellOffset);

    for (auto& row : grid)
        row.resize(mesh->ny + ghostCellOffset, defualtValue);
}

void Field::Initialize(std::function<double(double, double)> initializeFunction)
{
    for (std::size_t row_id = 0; row_id < grid.size(); ++row_id)
    {
        for (std::size_t column_id = 0; column_id < grid.at(0).size(); ++ column_id)
        {
            grid[row_id][column_id] = initializeFunction(row_id * mesh->dx, column_id * mesh->dy);
        }
    }
}

void Field::ApplyBoundaryCondition( BoundaryCondition::BoundaryConditionBase& top
                                  , BoundaryCondition::BoundaryConditionBase& bottom
                                  , BoundaryCondition::BoundaryConditionBase& left
                                  , BoundaryCondition::BoundaryConditionBase& right)
{
    top.Apply(mesh->dx);
    bottom.Apply(mesh->dx);
    left.Apply(mesh->dy);
    right.Apply(mesh->dy);
}

//check if appropriate for sure
BoundaryIndicies Field::GetBoundaryCells(const BoundaryCellsDirection direction) const
{
    BoundaryIndicies boundaryIndicies;
    switch (direction)
    {
        case BoundaryCellsDirection::Top:
            boundaryIndicies.reserve(grid.at(0).size());

            for (std::size_t columnId = 0; columnId < grid.at(0).size(); ++columnId)
                boundaryIndicies.push_back({0, columnId});

            break;
        case BoundaryCellsDirection::Bottom:
            boundaryIndicies.reserve(grid.at(grid.size() - 1).size());

            for (std::size_t columnId = 0; columnId < grid.at(0).size(); ++columnId)
                boundaryIndicies.push_back({grid.size() - 1, columnId});

            break;
        case BoundaryCellsDirection::Left:
            boundaryIndicies.reserve(grid.size());

            for (std::size_t rowId = 0; rowId < grid.size(); ++rowId)
                boundaryIndicies.push_back({rowId, 0});

            break;
        case BoundaryCellsDirection::Right:
            boundaryIndicies.reserve(grid.size());

            for (std::size_t rowId = 0; rowId < grid.size(); ++rowId)
                boundaryIndicies.push_back({rowId, grid.at(0).size() - 1});

            break;
    }

    return boundaryIndicies;
}

//todo make single fuction with additional parameter
BoundaryIndicies Field::GetAlignedCells(const BoundaryCellsDirection direction) const
{
    BoundaryIndicies alignedIndicies;
    switch (direction)
    {
        case BoundaryCellsDirection::Top:
            alignedIndicies.reserve(grid.at(0).size());

            for (std::size_t columnId = 0; columnId < grid.at(0).size(); ++columnId)
                alignedIndicies.push_back({1, columnId});

            break;
        case BoundaryCellsDirection::Bottom:
            alignedIndicies.reserve(grid.at(grid.size() - 1).size());

            for (std::size_t columnId = 0; columnId < grid.at(0).size(); ++columnId)
                alignedIndicies.push_back({grid.size() - 2, columnId});

            break;
        case BoundaryCellsDirection::Left:
            alignedIndicies.reserve(grid.size());

            for (std::size_t rowId = 0; rowId < grid.size(); ++rowId)
                alignedIndicies.push_back({rowId, 1});

            break;
        case BoundaryCellsDirection::Right:
            alignedIndicies.reserve(grid.size());

            for (std::size_t rowId = 0; rowId < grid.size(); ++rowId)
                alignedIndicies.push_back({rowId, grid.at(0).size() - 2});

            break;
    }

    return alignedIndicies;
}
