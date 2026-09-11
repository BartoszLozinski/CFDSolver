#include <gtest/gtest.h>

#include "PropertiesReaderTests.hpp"

TEST(ConfigurationTest, AssertTrue)
{
    ASSERT_TRUE(true);
}

int main(int argc, char** argv)
{
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}