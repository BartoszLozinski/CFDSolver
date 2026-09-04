#include "Solver.hpp"

#include "../../Field/Field.hpp"
#include "../../BoundaryCondition/Direchlet.hpp"
#include "../../BoundaryCondition/Neumann.hpp"

#include <iostream>
#include <format>

namespace Solver
{
    ExplicitHeatConduction::ExplicitHeatConduction(const MaterialProperties& materialProperties_, const double dt_)
        : materialProperties(materialProperties_)
        , dt(dt_)
    {};

    void ExplicitHeatConduction::Solve(const Mesh& mesh, [[maybe_unused]] const uint32_t timeSteps)
    {
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

        const auto dx = mesh.dx;
        const auto dy = mesh.dy;
        
        const auto alfa = materialProperties.thermalConductivity / (materialProperties.specificHeatCapacity * materialProperties.density);
        auto rx = alfa * dt / (dx * dx);
        auto ry = alfa * dt / (dy * dy);

        if (rx + ry > 0.5)
        {
            std::cout << "Warning: The solution may be unstable. Timestep will be adjusted.\n";
            dt = 0.9 * dx * dx / (2.0 * alfa * (dx *dx + dy * dy));
            rx = alfa * dt / (dx * dx);
            ry = alfa * dt / (dy * dy); 
            std::cout << std::format("New timestep: {}\n", dt);            
        }

        auto Tprevious = T.grid;

        for (std::size_t timestep = 0; timestep < timeSteps; ++timestep)
        {
            Tprevious = T.grid;
            T.ApplyBoundaryCondition(bcTop, bcBottom, bcLeft, bcRight);

            static constexpr std::size_t ghostCellOffset = 1;
            for (std::size_t xi = ghostCellOffset; xi < mesh.nx; ++xi)
            {
                for (std::size_t yi = ghostCellOffset; yi < mesh.ny; ++yi)
                {
                    T.grid[xi][yi] = (Tprevious[xi + 1][yi] + Tprevious[xi - 1][yi]) * rx + 
                                     (Tprevious[xi][yi + 1] + Tprevious[xi][yi - 1]) * ry + 
                                     (Tprevious[xi][yi] * (1.0 - 2.0 * (rx + ry)));

                    // todo export for visualization
                    // todo add time measurement
                }
            }
        }
    }
}
