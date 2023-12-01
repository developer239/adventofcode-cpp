#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay22_6, SuccessCase) {
  EXPECT_EQ(5, runPart1("./assets/input-example-1.txt"));
  EXPECT_EQ(6, runPart1("./assets/input-example-2.txt"));
  EXPECT_EQ(10, runPart1("./assets/input-example-3.txt"));
  EXPECT_EQ(11, runPart1("./assets/input-example-4.txt"));
  EXPECT_EQ(19, runPart2("./assets/input-example-5.txt"));
  EXPECT_EQ(23, runPart2("./assets/input-example-6.txt"));
  EXPECT_EQ(23, runPart2("./assets/input-example-7.txt"));
  EXPECT_EQ(29, runPart2("./assets/input-example-8.txt"));
  EXPECT_EQ(26, runPart2("./assets/input-example-9.txt"));
}
