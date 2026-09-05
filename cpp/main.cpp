#include "Solvers/HeatConductionSolver/Solver.hpp"
#include "Solvers/HeatConductionSolver/MaterialProperties.hpp"
#include "Mesh/MeshGenerator.hpp"

#include <chrono>
#include <iostream>
#include <format>

using Clock = std::chrono::steady_clock;

int main()
{

    const MaterialProperties materialProperties{16.0, 7850.0, 500.0};
    const auto mesh = MeshGenerator{}.GenerateMesh(0.1, 0.1, 20, 20);
    static constexpr double dt = 100; // [s]

    static constexpr bool shouldExportResults = true;
    static constexpr uint32_t exportFrequency = 100;
    Solver::ExplicitHeatConduction solver{ materialProperties, dt, shouldExportResults, exportFrequency };

    static constexpr uint32_t timesteps = 500;
    const auto start = Clock::now();
    
    solver.Solve(mesh, timesteps);
    
    const auto end = Clock::now();
    const std::chrono::duration<double> elapsed = end - start;
    std::cout << std::format("Time elapsed: {} [s]\n", elapsed.count());

    return 0;
};