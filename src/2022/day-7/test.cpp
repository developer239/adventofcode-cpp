#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay7, SuccessCase) {
  EXPECT_EQ(5, runPart1("./assets/input-example.txt"));
}
