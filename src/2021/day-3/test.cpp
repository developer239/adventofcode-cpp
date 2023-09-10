#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay3, SuccessCase) {
  EXPECT_EQ(198, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(230, runPart2("./assets/input-example.txt"));
}
