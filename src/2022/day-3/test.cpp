#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_3, SuccessCase) {
  EXPECT_EQ(157, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(70, runPart2("./assets/input-example-2.txt"));
}
