#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_7, SuccessCase) {
  EXPECT_EQ(345015, runPart1("./assets/input.txt"));
  EXPECT_EQ(42588603, runPart2("./assets/input.txt"));
}
