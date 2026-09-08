#pragma once

#include "../../Properties/MaterialProperties.hpp"
#include "../../Mesh/Mesh.hpp"

namespace Solver
{
    class ExplicitHeatConduction
    {
    private:
        MaterialProperties materialProperties;
        double dt;
        bool shouldExportResults{ false };
        uint32_t exportFrequency{};

    public:
        ExplicitHeatConduction(const MaterialProperties& materialProperties_, const double dt_, const bool shouldExportResults_ = false, const uint32_t exportFrequency_ = 0);

        void Solve(const Mesh& mesh, const uint32_t timeSteps);
    };
};
