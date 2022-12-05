#include <gtest/gtest.h>

#include "./Day.cpp"

// TODO: rename to TestDay5
TEST(TestDay05, SuccessCase) {
  EXPECT_EQ("MCD", runPart1("./assets/input.txt"));
//  EXPECT_EQ(4, runPart2("./assets/input-example.txt"));
}
