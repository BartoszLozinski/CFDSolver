#include "ImplicitHeatConduction.hpp"

#include "../../BoundaryCondition/Direchlet.hpp"
#include "../../BoundaryCondition/Neumann.hpp"
#include "../../Field/Field.hpp"
#include "../../ResultsExporter/CSVExporter.hpp"

#include <algorithm>
#include <cmath>
#include <format>
#include <iostream>
#include <limits>
#include <stdexcept>
#include <utility>
#include <vector>

namespace Solver
{
    namespace FiniteDifference
    {
        namespace Implicit
        {
            HeatConduction::HeatConduction(const MaterialProperties& materialProperties_, const SimulationProperties& simulationProperties_)
                : SolverBase(materialProperties_, simulationProperties_)
            {};

            std::size_t HeatConduction::Index(const Mesh& mesh, const std::size_t ix, const std::size_t iy) const
            {
                static constexpr std::size_t ghostCellOffset = 1;
                return (ix - ghostCellOffset) * mesh.ny + (iy - ghostCellOffset);
            }

            //will be moved to Math library
            HeatConduction::DenseMatrix HeatConduction::BuildMatrix(const Mesh& mesh, const double rx, const double ry) const
            {
                static constexpr double defaultValue = 0.0;
                DenseMatrix matrix(mesh.nx * mesh.ny,
                                   std::vector<double>(mesh.nx * mesh.ny, defaultValue));

                // TODO: right now with zero gradient BC - to be updated some day

                for (std::size_t ix = 1; ix <= mesh.nx; ++ix)
                {
                    for (std::size_t iy = 1; iy <= mesh.ny; ++iy)
                    {
                        const auto row = Index(mesh, ix, iy);
                        auto diagonal = 1.0 + 2.0 * rx + 2.0 * ry;

                        // Top and bottom are Dirichlet boundaries. Their known
                        // temperatures are added to the right-hand side in Solve.
                        if (ix > 1)
                            matrix[row][Index(mesh, ix - 1, iy)] = -rx;
                        if (ix < mesh.nx)
                            matrix[row][Index(mesh, ix + 1, iy)] = -rx;

                        // Left and right are zero-gradient Neumann boundaries.
                        if (iy > 1)
                            matrix[row][Index(mesh, ix, iy - 1)] = -ry;
                        else
                            diagonal -= ry;

                        if (iy < mesh.ny)
                            matrix[row][Index(mesh, ix, iy + 1)] = -ry;
                        else
                            diagonal -= ry;

                        matrix[row][row] = diagonal;
                    }
                }

                return matrix;
            }

            std::vector<double> SolveLinearSystem(HeatConduction::DenseMatrix matrix, std::vector<double> rhs)
            {
                static constexpr double pivotTolerance = 1e-12;

                for (std::size_t pivot = 0; pivot < rhs.size(); ++pivot)
                {
                    auto pivotRow = pivot;
                    for (std::size_t row = pivot + 1; row < rhs.size(); ++row)
                    {
                        if (std::abs(matrix[row][pivot]) > std::abs(matrix[pivotRow][pivot]))
                            pivotRow = row;
                    }

                    if (std::abs(matrix[pivotRow][pivot]) < pivotTolerance)
                        throw std::runtime_error("Implicit heat-conduction matrix is singular.");

                    std::swap(matrix[pivot], matrix[pivotRow]);
                    std::swap(rhs[pivot], rhs[pivotRow]);

                    for (std::size_t row = pivot + 1; row < rhs.size(); ++row)
                    {
                        const auto factor = matrix[row][pivot] / matrix[pivot][pivot];
                        matrix[row][pivot] = 0.0;

                        for (std::size_t column = pivot + 1; column < rhs.size(); ++column)
                            matrix[row][column] -= factor * matrix[pivot][column];

                        rhs[row] -= factor * rhs[pivot];
                    }
                }

                std::vector<double> solution(rhs.size(), 0.0);
                for (std::size_t row = rhs.size(); row-- > 0;)
                {
                    auto value = rhs[row];
                    for (std::size_t column = row + 1; column < rhs.size(); ++column)
                        value -= matrix[row][column] * solution[column];

                    solution[row] = value / matrix[row][row];
                }

                return solution;
            }

            void HeatConduction::Solve(const Mesh& mesh, const std::string_view finalResultPath)
            {
                // TODO add boundary conditions to the setup file
                // Probably mesh generator would have to create a mesh, store indicies
                // and name specified indiecies for a boundaryCondition (also aligned if Neumann?)
                // or maybe modify it when moved to FVM as BC should be applied at faces

                //to move to separate function
                const double T_top = 373.0; // [K]
                const double T_bottom = 273.0; // [K]
                const double T_initInternal = 300.0; // [K]

                static constexpr std::size_t ghostCellOffset = 1;

                Field T(mesh);
                T.Initialize([T_initInternal](double, double) { return T_initInternal; });

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

                const auto dx = mesh.dx;
                const auto dy = mesh.dy;
                const auto rx = alfa * dt / (dx * dx);
                const auto ry = alfa * dt / (dy * dy);
                const auto matrix = BuildMatrix(mesh, rx, ry);

                double maxResidual = std::numeric_limits<double>::infinity();
                std::size_t timestep = 0;

                while (timestep < simulationProperties.timesteps && maxResidual >= simulationProperties.tolerance)
                {
                    maxResidual = 0;
                    T.ApplyBoundaryCondition(bcTop, bcBottom, bcLeft, bcRight);

                    // The matrix contains only physical-cell unknowns. Ghost
                    // cells are applied to T before forming the previous field.
                    const auto previous = T.grid;
                    std::vector<double> rhs(mesh.nx * mesh.ny, 0.0);

                    for (std::size_t xi = ghostCellOffset; xi <= mesh.nx; ++xi)
                    {
                        for (std::size_t yi = ghostCellOffset; yi <= mesh.ny; ++yi)
                        {
                            const auto row = Index(mesh, xi, yi);
                            rhs[row] = previous[xi][yi];

                            if (xi == ghostCellOffset)
                                rhs[row] += rx * T_top;
                            if (xi == mesh.nx)
                                rhs[row] += rx * T_bottom;
                        }
                    }

                    const auto solution = SolveLinearSystem(matrix, std::move(rhs));
                    for (std::size_t xi = ghostCellOffset; xi <= mesh.nx; ++xi)
                    {
                        for (std::size_t yi = ghostCellOffset; yi <= mesh.ny; ++yi)
                        {
                            const auto value = solution[Index(mesh, xi, yi)];
                            maxResidual = std::max(maxResidual, std::abs(value - previous[xi][yi]));
                            T.grid[xi][yi] = value;
                        }
                    }

                    // Refresh ghost cells before exporting and before the next step.
                    T.ApplyBoundaryCondition(bcTop, bcBottom, bcLeft, bcRight);

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
