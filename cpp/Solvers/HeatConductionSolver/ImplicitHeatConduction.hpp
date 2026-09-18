#pragma once

#include "SolverBase.hpp"
#include "../../Mesh/Mesh.hpp"

#include <string_view>
#include <vector>

namespace Solver
{
    namespace FiniteDifference
    {
        namespace Implicit
        {
            class HeatConduction : public SolverBase
            {
            public:
                using DenseMatrix = std::vector<std::vector<double>>;

            private:
                [[nodiscard]] std::size_t Index(const Mesh& mesh, const std::size_t ix, const std::size_t iy) const;
                [[nodiscard]] DenseMatrix BuildMatrix(const Mesh& mesh, const double rx, const double ry) const;

            public:
                HeatConduction(const MaterialProperties& materialProperties_, const SimulationProperties& simulationProperties_);
                void Solve(const Mesh& mesh, std::string_view finalResultPath = {}) override;
            };
        }
    }
};
