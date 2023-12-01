#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_7, SuccessCase) {
  EXPECT_EQ(95437, runPart1("./assets/input-example.txt"));
  EXPECT_EQ(24933642, runPart2("./assets/input-example.txt"));
}
