#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay23_4, SuccessCase) {
  EXPECT_EQ(20855, runPart1("./assets/input.txt"));
  EXPECT_EQ(5489600, runPart2("./assets/input.txt"));
}
