#pragma once

#include "../../Properties/MaterialProperties.hpp"
#include "../../Properties/SimulationProperties.hpp"
#include "../../Mesh/Mesh.hpp"

#include <string_view>


class SolverBase
{
protected:
    MaterialProperties materialProperties;
    SimulationProperties simulationProperties;

public:
    virtual ~SolverBase() = default;
    SolverBase(const MaterialProperties& materialProperties_, const SimulationProperties& simulationProperties_);
    virtual void Solve(const Mesh& mesh, std::string_view finalResultPath = {}) = 0;
};
