#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay21_2, SuccessCase) {
  EXPECT_EQ(150, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(900, runPart2("./assets/input-example.txt"));
}
