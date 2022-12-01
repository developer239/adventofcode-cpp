#include <gtest/gtest.h>

int countCalories() {
  return 2;
}

TEST(TestCase, FailingTest) {
  EXPECT_EQ(1, countCalories());
}
