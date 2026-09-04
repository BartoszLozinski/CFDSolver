#pragma once
#include "../Mesh/Mesh.hpp"
#include "../BoundaryCondition/BoundaryConditionBase.hpp"
#include <vector>
#include <functional>

// TODO move to separate library
// TODO make Field class a templated when needed to calculate vectors
// i.e velocity

enum class BoundaryCellsDirection
{
    Top,
    Bottom,
    Left,
    Right,
};

class Field
{
private:
    const Mesh* mesh = nullptr;

public:
    Grid grid;
    
    Field(const Mesh& mesh_);
    void Initialize(std::function<double(double, double)> initializeFunction);

    BoundaryIndicies GetBoundaryCells(const BoundaryCellsDirection direction) const;
    BoundaryIndicies GetAlignedCells(const BoundaryCellsDirection direction) const;

    void ApplyBoundaryCondition( BoundaryCondition::BoundaryConditionBase& top
                               , BoundaryCondition::BoundaryConditionBase& bottom
                               , BoundaryCondition::BoundaryConditionBase& left
                               , BoundaryCondition::BoundaryConditionBase& right);
};