#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_12, SuccessCase) {
  EXPECT_EQ(31, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(29, runPart2("./assets/input-example.txt"));
}
