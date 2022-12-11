#include <iostream>

#include "Day.cpp"

int main() {
  auto result1 = runPart1("./assets/input.txt");

  std::cout << "Part 1: " << result1 << std::endl;

  runPart2("./assets/input.txt");

  return 0;
}
