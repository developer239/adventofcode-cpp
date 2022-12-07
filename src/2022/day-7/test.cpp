#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay7, SuccessCase) {
  EXPECT_EQ(95437, runPart1("./assets/input-example.txt"));
}
