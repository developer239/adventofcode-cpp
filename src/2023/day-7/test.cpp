#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_7, SuccessCase) {
  EXPECT_EQ(249631254, runPart2("./assets/input.txt"));
}
