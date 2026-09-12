#include "Solver.hpp"

#include "../../Field/Field.hpp"
#include "../../BoundaryCondition/Direchlet.hpp"
#include "../../BoundaryCondition/Neumann.hpp"
#include "../../MathOperators/Laplacian.hpp"
#include "../../ResultsExporter/CSVExporter.hpp"

#include <iostream>
#include <format>

namespace Solver
{
    namespace FiniteDifference
    {
        namespace Explicit
        {
            HeatConduction::HeatConduction(const MaterialProperties& materialProperties_, const SimulationProperties& simulationProperties_)
                : materialProperties(materialProperties_)
                , simulationProperties(simulationProperties_)
            {};

            void HeatConduction::Solve(const Mesh& mesh)
            {
                //TODO add boundary conditions to the setup file
                const double T_top = 373.0; // [K]
                const double T_bottom = 273.0; // [K]

                Field T(mesh);
                T.Initialize([](double, double) { return 300.0; });

                auto bcTop = BoundaryCondition::Direchlet( T.grid
                                                        , T.GetBoundaryCells(BoundaryCellsDirection::Top)
                                                        , [&](double, double) { return T_top; });
                
                auto bcBottom = BoundaryCondition::Direchlet( T.grid
                                                            , T.GetBoundaryCells(BoundaryCellsDirection::Bottom)
                                                            , [&](double, double) { return T_bottom; });
                
                auto bcLeft = BoundaryCondition::Neumann( T.grid
                                                    , T.GetBoundaryCells(BoundaryCellsDirection::Left)
                                                    , [&](double, double, double alignedCellValue) { return alignedCellValue; }
                                                    , T.GetAlignedCells(BoundaryCellsDirection::Left) );
                
                auto bcRight = BoundaryCondition::Neumann( T.grid
                                                        , T.GetBoundaryCells(BoundaryCellsDirection::Right)
                                                        , [&](double, double, double alignedCellValue) { return alignedCellValue; }
                                                        , T.GetAlignedCells(BoundaryCellsDirection::Right) );

                
                auto& dt = simulationProperties.dt;
                const auto alfa = materialProperties.thermalConductivity / (materialProperties.specificHeatCapacity * materialProperties.density);
                
                {
                    const auto dx = mesh.dx;
                    const auto dy = mesh.dy;
                    const auto rx = alfa * dt / (dx * dx);
                    const auto ry = alfa * dt / (dy * dy);

                    if ((rx + ry) > 0.5)
                    {
                        std::cout << "Warning: The solution may be unstable. Timestep will be adjusted.\n";
                        dt = 0.9 * dx * dx * dy * dy/ (2.0 * alfa * (dx * dx + dy * dy));
                        std::cout << std::format("New timestep: {}\n", dt);            
                    }
                }
                
                auto Tprevious = T.grid;
                Operators::Laplacian laplacian{ mesh.dx, mesh.dy, Tprevious };

                for (std::size_t timestep = 0; timestep <= simulationProperties.timesteps; ++timestep)
                {
                    Tprevious = T.grid;
                    T.ApplyBoundaryCondition(bcTop, bcBottom, bcLeft, bcRight);

                    static constexpr std::size_t ghostCellOffset = 1;
                    for (std::size_t xi = ghostCellOffset; xi <= mesh.nx; ++xi)
                    {
                        for (std::size_t yi = ghostCellOffset; yi <= mesh.ny; ++yi)
                        {
                            T.grid[xi][yi] = Tprevious[xi][yi] + alfa * dt * laplacian(xi, yi);
                        }
                    }

                    if (simulationProperties.shouldExportResults && timestep % simulationProperties.exportFrequency == 0)
                    {
                        std::string filename = std::format("Results/T/{}.csv", timestep);
                        CSVExporter exporter;
                        exporter.Export(filename, T.grid);
                    }
                }
            }
        }
    }
}
