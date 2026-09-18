#include "SolverBase.hpp"

SolverBase::SolverBase(const MaterialProperties& materialProperties_, const SimulationProperties& simulationProperties_)
    : materialProperties(materialProperties_)
    , simulationProperties(simulationProperties_)
{};

