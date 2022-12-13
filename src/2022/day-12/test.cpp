#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay12, SuccessCase) {
  EXPECT_EQ(31, runPart1("./assets/input-example.txt"));
}
