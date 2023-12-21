#include <iostream>

#include "Day.cpp"

int main() {
  auto result1 = runPart1("./assets/input.txt");
  auto result2 = runPart2("./assets/input-example-5.txt");

  std::cout << "Part 1: " << result1 << std::endl;
  std::cout << "Part 2: " << result2 << std::endl;

  return 0;
}
