#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_2, SuccessCase) {
  EXPECT_EQ(2551, runPart1("./assets/input.txt"));
  EXPECT_EQ(62811, runPart2("./assets/input.txt"));
}
