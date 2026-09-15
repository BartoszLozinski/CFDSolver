#pragma once

#include <gtest/gtest.h>

#include "Mesh/MeshGenerator.hpp"
#include "Properties/MaterialProperties.hpp"
#include "Properties/SimulationProperties.hpp"
#include "Solvers/HeatConductionSolver/ExplicitHeatConduction.hpp"

#include <filesystem>
#include <fstream>

TEST(HeatConductionSolverTests, ConvergesToLinearOneDimensionalTemperatureProfile)
{
	const std::filesystem::path resultPath{"Results/T/TestResult.csv"};
	std::filesystem::remove(resultPath);

	const MaterialProperties materialProperties{
		.thermalConductivity = 1.0,
		.specificHeatCapacity = 1.0,
		.density = 1.0
	};
	const SimulationProperties simulationProperties{
		.dt = 0.1,
		.shouldExportResults = true,
		.exportFrequency = 5000,
		.timesteps = 5000,
		.tolerance = 1e-6
	};
	const Mesh mesh = MeshGenerator{}.GenerateMesh(1.0, 1.0, 8, 1);

	Solver::FiniteDifference::Explicit::HeatConduction solver{
		materialProperties,
		simulationProperties
	};


	solver.Solve(mesh, resultPath.string());


	std::ifstream resultFile{resultPath};
	ASSERT_TRUE(resultFile.is_open());
    static constexpr double resultTolerance = 1e-3;
    static constexpr std::size_t ghostCellsOffset = 2;
    static constexpr double hardcodedTTop = 373.0;
    static constexpr double hardcodedTBottom = 273.0;

    double value{};
	for (std::size_t row = 0; row < (mesh.nx + ghostCellsOffset); ++row)
	{
		const double expectedTemperature =
			hardcodedTTop + static_cast<double>(row) / (mesh.nx + 1) * (hardcodedTBottom - hardcodedTTop);

		for (std::size_t column = 0; column < (mesh.ny + ghostCellsOffset); ++column)
		{
			ASSERT_TRUE(resultFile >> value);
			EXPECT_NEAR(value, expectedTemperature, resultTolerance);
		}
	}

	resultFile.close();
	std::filesystem::remove(resultPath);
}
