#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_13, SuccessCase) {
  EXPECT_EQ(13, runPart1("./assets/input-example.txt"));
}
