#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay9, SuccessCase) {
  EXPECT_EQ(13, runPart1("./assets/input.txt"));
//  EXPECT_EQ(8, runPart2("./assets/input-example.txt"));
}
