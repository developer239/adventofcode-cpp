#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay2, SuccessCase) {
  EXPECT_EQ(15, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(12, runPart2("./assets/input-example.txt"));
}
