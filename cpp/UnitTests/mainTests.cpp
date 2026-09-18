#include <gtest/gtest.h>

#include "ExplicitHeatConductionSolverTests.hpp"
#include "ImplicitHeatConductionSolverTests.hpp"
#include "MathOperatorsTests.hpp"
#include "PropertiesReaderTests.hpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}