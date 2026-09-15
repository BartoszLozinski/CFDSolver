#pragma once

#include "../../Properties/MaterialProperties.hpp"
#include "../../Properties/SimulationProperties.hpp"
#include "../../Mesh/Mesh.hpp"

#include <string_view>

namespace Solver
{
    namespace FiniteDifference
    {
        namespace Explicit
        {
            class HeatConduction
            {
            private:
                MaterialProperties materialProperties;
                SimulationProperties simulationProperties;

            public:
                HeatConduction(const MaterialProperties& materialProperties_, const SimulationProperties& simulationProperties_);
                void Solve(const Mesh& mesh, std::string_view finalResultPath = {});
            };
        }
    }
};
