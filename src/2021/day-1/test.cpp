#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay1, SuccessCase) {
  EXPECT_EQ(7, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(5, runPart2("./assets/input-example.txt"));
}
