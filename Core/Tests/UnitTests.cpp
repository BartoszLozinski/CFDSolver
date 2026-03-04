#include "MeshTests.hpp"
#include "FieldTests.hpp"
#include "BoundaryConditionTests.hpp"

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
