#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_8, SuccessCase) {
  EXPECT_EQ(21, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(8, runPart2("./assets/input-example.txt"));
}
