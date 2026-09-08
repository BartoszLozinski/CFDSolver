#include "Solvers/HeatConductionSolver/Solver.hpp"
#include "Properties/MaterialProperties.hpp"
#include "Mesh/MeshGenerator.hpp"
#include "PropertiesReader/MaterialPropertiesReader.hpp"
#include "PropertiesReader/MeshPropertiesReader.hpp"

#include <chrono>
#include <iostream>
#include <format>

using Clock = std::chrono::steady_clock;

int main()
{
    const auto materialProperties = MaterialPropertiesReader{}.ReadFromSetupFile();
    const auto mesh = MeshGenerator{}.GenerateMesh(MeshPropertiesReader{}.ReadFromSetupFile());

    // Todo add properties reader for simulation config
    static constexpr double dt = 200; // [s]
    static constexpr bool shouldExportResults = true;
    static constexpr uint32_t exportFrequency = 100;
    static constexpr uint32_t timesteps = 1000;

    Solver::ExplicitHeatConduction solver{ materialProperties, dt, shouldExportResults, exportFrequency };

    const auto start = Clock::now();
    solver.Solve(mesh, timesteps);
    const auto end = Clock::now();

    const std::chrono::duration<double> elapsed = end - start;
    std::cout << std::format("Time elapsed: {} [s]\n", elapsed.count());

    return 0;
};