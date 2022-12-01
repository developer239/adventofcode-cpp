#include <gtest/gtest.h>

#include "../Day.cpp"

TEST(TestCase, SuccessCase) {
  EXPECT_EQ(24000, countCaloriesPart1("../../../../src/day-1/input-example.txt"));
  EXPECT_EQ(45000, countCaloriesPart2("../../../../src/day-1/input-example.txt"));
}
