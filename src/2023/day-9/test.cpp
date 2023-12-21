#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_9, SuccessCase) {
  EXPECT_EQ(0, runPart1("./assets/input.txt"));
  EXPECT_EQ(0, runPart2("./assets/input.txt"));
}
