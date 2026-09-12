#include <gtest/gtest.h>

#include "MathOperatorsTests.hpp"
#include "PropertiesReaderTests.hpp"

// TODO add UT for 1D heat conduction solver
// When applied solver stop condition at the steady state
// Compare with analytical solution

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}