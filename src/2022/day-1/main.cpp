#include <iostream>

#include "Day.cpp"

int main() {
  auto result1 = countCaloriesPart1("./assets/input.txt");
  auto result2 = countCaloriesPart2("./assets/input.txt");

  std::cout << "Part 1: " << result1 << std::endl;
  std::cout << "Part 2: " << result2 << std::endl;

  return 0;
}
