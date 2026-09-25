#include <gtest/gtest.h>

#include "lib.h"

TEST(VersionTest, VersionIsPositive)
{
    EXPECT_GT(version(), 0);
}