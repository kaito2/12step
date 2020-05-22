#include "gtest/gtest.h"
#include "mylib.h"

// main 関数がないと起こられる
int main(int argc, char **argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

TEST(TestCaseName, TestName)
{
    char *s1 = "abcd";
    char *s2 = "abcd";
    char *s3 = "aaaa";
    EXPECT_EQ(0, my_strcmp(s1, s2));
}