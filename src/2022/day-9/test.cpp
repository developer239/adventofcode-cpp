#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_9, SuccessCase) {
  EXPECT_EQ(13, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(36, runPart2("./assets/input-example-2.txt"));
}
