#include "ExplicitHeatConduction.hpp"

#include "../../Field/Field.hpp"
#include "../../BoundaryCondition/Direchlet.hpp"
#include "../../BoundaryCondition/Neumann.hpp"
#include "../../MathOperators/Laplacian.hpp"
#include "../../ResultsExporter/CSVExporter.hpp"

#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <limits>

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

            void HeatConduction::Solve(const Mesh& mesh, const std::string_view finalResultPath)
            {
                // TODO add boundary conditions to the setup file
                // Probably mesh generator would have to create a mesh, store indicies
                // and name specified indiecies for a boundaryCondition (also aligned if Neumann?)
                // or maybe modify it when moved to FVM as BC should be applied at faces
                
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
                double maxResidual = std::numeric_limits<double>::infinity();
                std::size_t timestep = 0;

                while (timestep < simulationProperties.timesteps && maxResidual >= simulationProperties.tolerance)
                {
                    maxResidual = 0;
                    T.ApplyBoundaryCondition(bcTop, bcBottom, bcLeft, bcRight);
                    Tprevious = T.grid;

                    static constexpr std::size_t ghostCellOffset = 1;
                    for (std::size_t xi = ghostCellOffset; xi <= mesh.nx; ++xi)
                    {
                        for (std::size_t yi = ghostCellOffset; yi <= mesh.ny; ++yi)
                        {
                            T.grid[xi][yi] = Tprevious[xi][yi] + alfa * dt * laplacian(xi, yi);
                            maxResidual = std::max(maxResidual, std::abs(T.grid[xi][yi] - Tprevious[xi][yi]));
                        }
                    }

                    if (simulationProperties.shouldExportResults && finalResultPath.empty() && timestep % simulationProperties.exportFrequency == 0)
                    {
                        std::string filename = std::format("Results/T/{}.csv", timestep);
                        CSVExporter exporter;
                        exporter.Export(filename, T.grid);
                    }

                    ++timestep;                    
                }

                // TODO add result export to the separate class and lib
                std::cout << std::format("Finished after {} timesteps ({} [s])\n", timestep, timestep * dt);
            
                if (simulationProperties.shouldExportResults)
                {
                    std::string filename = finalResultPath.empty()
                        ? std::format("Results/T/{}.csv", timestep)
                        : std::string{finalResultPath};
                    CSVExporter exporter;
                    exporter.Export(filename, T.grid);
                }
            }
        }
    }
}
