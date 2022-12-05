#include <gtest/gtest.h>

#include "./Day.cpp"

// TODO: rename to TestDay5
TEST(TestDay05, SuccessCase) {
  EXPECT_EQ("CMZ", runPart1("./assets/input-example.txt"));
  EXPECT_EQ("MCD", runPart2("./assets/input-example.txt"));
}
