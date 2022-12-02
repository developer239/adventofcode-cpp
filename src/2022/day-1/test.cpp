#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestCase, SuccessCase) {
  EXPECT_EQ(24000, countCaloriesPart1("./assets/input-example.txt"));
  EXPECT_EQ(45000, countCaloriesPart2("./assets/input-example.txt"));
}
