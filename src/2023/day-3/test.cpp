#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_3, SuccessCase) {
  EXPECT_EQ(553079, runPart1("./assets/input.txt"));
  EXPECT_EQ(84363105, runPart2("./assets/input.txt"));
}
