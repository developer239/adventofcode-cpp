#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay4, SuccessCase) {
  EXPECT_EQ(2, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(4, runPart2("./assets/input-example.txt"));
}
