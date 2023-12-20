#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_8, SuccessCase) {
  EXPECT_EQ(55834, runPart1("./assets/input.txt"));
  EXPECT_EQ(53221, runPart2("./assets/input.txt"));
}
