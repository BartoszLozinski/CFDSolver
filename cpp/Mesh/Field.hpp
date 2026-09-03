#pragma once
#include "Mesh.hpp"
#include <vector>
#include <functional>

// TODO move to separate library
// TODO make Field class a templated when needed to calculate vectors
// i.e velocity

using Grid = std::vector<std::vector<double>>;

class Field
{
private:
    const Mesh& mesh;
    Grid grid;

public:
    Field(const Mesh& mesh_);
    void Initialize(std::function<double(double, double)> initializeFunction);
    void SetBoundaryConditions(); //TODO
};