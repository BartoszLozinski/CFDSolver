#include "MeshTests.hpp"
#include "FieldTests.hpp"
#include "BoundaryConditionTests.hpp"
#include "VectorNtTests.hpp"
#include "GradientTests.hpp"
#include "DivergenceTests.hpp"
#include "LaplacianTests.hpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
