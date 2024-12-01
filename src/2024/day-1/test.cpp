#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_1, SuccessCase) {
  EXPECT_EQ(2367773, runPart1("./assets/input.txt"));
  EXPECT_EQ(21271939, runPart2("./assets/input.txt"));
}
