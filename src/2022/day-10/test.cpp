#include <gtest/gtest.h>

#include "./Day.cpp"

TEST(TestDay10, SuccessCase) {
  EXPECT_EQ(13140, runPart1("./assets/input-example.txt"));
}
