#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_11, SuccessCase) {
  EXPECT_EQ(10605, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(2713310158, runPart2("./assets/input-example.txt"));
}
