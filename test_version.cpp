#include<gtest/gtest.h>
#include "lib.h"

TEST(VersionTest, TestVersion){
    EXPECT_LT(0,version());
}