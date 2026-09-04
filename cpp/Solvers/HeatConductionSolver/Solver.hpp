#pragma once

#include "MaterialProperties.hpp"
#include "../../Mesh/Mesh.hpp"

namespace Solver
{
    class ExplicitHeatConduction
    {
    private:
        MaterialProperties materialProperties;
        double dt;

    public:
        ExplicitHeatConduction(const MaterialProperties& materialProperties_, const double dt_);

        void Solve(const Mesh& mesh, const uint32_t timeSteps);
    };
};
