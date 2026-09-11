#pragma once

#include "../../Properties/MaterialProperties.hpp"
#include "../../Properties/SimulationProperties.hpp"
#include "../../Mesh/Mesh.hpp"

namespace Solver
{
    class ExplicitHeatConduction
    {
    private:
        MaterialProperties materialProperties;
        SimulationProperties simulationProperties;


    public:
        ExplicitHeatConduction(const MaterialProperties& materialProperties_, const SimulationProperties& simulationProperties_);

        void Solve(const Mesh& mesh);
    };
};
