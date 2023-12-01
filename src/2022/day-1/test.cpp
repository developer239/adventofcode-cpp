#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_1, SuccessCase) {
  EXPECT_EQ(24000, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(45000, runPart2("./assets/input-example.txt"));
}
