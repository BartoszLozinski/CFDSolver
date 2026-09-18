#pragma once

#include "SolverBase.hpp"
#include "../../Mesh/Mesh.hpp"

#include <string_view>

namespace Solver
{
    namespace FiniteDifference
    {
        namespace Implicit
        {
            class HeatConduction : public SolverBase
            {
            private:
            
            public:
                HeatConduction(const MaterialProperties& materialProperties_, const SimulationProperties& simulationProperties_);
                void Solve(const Mesh& mesh, std::string_view finalResultPath = {}) override;
            };
        }
    }
};
