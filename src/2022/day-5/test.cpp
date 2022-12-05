#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay5, SuccessCase) {
  EXPECT_EQ("CMZ", runPart1("./assets/input-example.txt"));
  EXPECT_EQ("MCD", runPart2("./assets/input-example.txt"));
}
