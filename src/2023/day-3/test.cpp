#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_3, SuccessCase) {
  EXPECT_EQ(99, runPart1("./assets/input.txt"));
  EXPECT_EQ(99, runPart2("./assets/input.txt"));
}
