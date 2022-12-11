#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay10, SuccessCase) {
  EXPECT_EQ(13140, runPart1("./assets/input.txt"));
//  EXPECT_EQ(36, runPart2("./assets/input-example-2.txt"));
}
