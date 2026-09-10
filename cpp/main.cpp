#include "Solvers/HeatConductionSolver/Solver.hpp"
#include "Properties/MaterialProperties.hpp"
#include "Mesh/MeshGenerator.hpp"
#include "PropertiesReader/MaterialPropertiesReader.hpp"
#include "PropertiesReader/MeshPropertiesReader.hpp"
#include "PropertiesReader/SimulationPropertiesReader.hpp"

#include <chrono>
#include <iostream>
#include <format>

using Clock = std::chrono::steady_clock;

int main()
{
    const auto materialProperties = MaterialPropertiesReader{}.ReadFromSetupFile();
    const auto mesh = MeshGenerator{}.GenerateMesh(MeshPropertiesReader{}.ReadFromSetupFile());
    const auto simulationProperties = SimulationPropertiesReader{}.ReadFromSetupFile();

    Solver::ExplicitHeatConduction solver{ materialProperties, simulationProperties.dt, simulationProperties.shouldExportResults, simulationProperties.exportFrequency };

    const auto start = Clock::now();
    solver.Solve(mesh, simulationProperties.timesteps);
    const auto end = Clock::now();

    const std::chrono::duration<double> elapsed = end - start;
    std::cout << std::format("Time elapsed: {} [s]\n", elapsed.count());

    return 0;
};