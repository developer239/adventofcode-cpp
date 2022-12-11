#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay11, SuccessCase) {
  EXPECT_EQ(0, runPart1("./assets/input-example.txt"));
}
