#include "Solvers/HeatConductionSolver/ExplicitHeatConduction.hpp"
#include "Solvers/HeatConductionSolver/ImplicitHeatConduction.hpp"
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
    const auto materialProperties = MaterialPropertiesReader{}.ReadFromSetupFile("Setup/MaterialProperties");
    const auto mesh = MeshGenerator{}.GenerateMesh(MeshPropertiesReader{}.ReadFromSetupFile("Setup/MeshProperties"));
    const auto simulationProperties = SimulationPropertiesReader{}.ReadFromSetupFile("Setup/SimulationProperties");
    
    /*
    Solver::FiniteDifference::Explicit::HeatConduction explicitSolver{ materialProperties, simulationProperties };
    
    auto start = Clock::now();
    explicitSolver.Solve(mesh);
    auto end = Clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << std::format("Time elapsed for explicit solver: {} [s]\n", elapsed.count());
    */

    
    Solver::FiniteDifference::Implicit::HeatConduction implicitSolver{ materialProperties, simulationProperties };

    auto start = Clock::now();
    implicitSolver.Solve(mesh);
    auto end = Clock::now();

    std::chrono::duration<double> elapsed = end - start;
    std::cout << std::format("Time elapsed for implicit solver: {} [s]\n", elapsed.count());

    
    return 0;
};