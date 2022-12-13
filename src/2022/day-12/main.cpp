#include <iostream>

#include "Day.cpp"

int measure() {
  return std::chrono::duration_cast<std::chrono::milliseconds>(
             std::chrono::system_clock::now().time_since_epoch()
  )
      .count();
}

void logResult(long long result, int start, int end) {
  std::cout << "Part 1: " << result << " in " << end - start << "ms"
            << std::endl;
}

int main() {
  auto start1 = measure();
  auto result1 = runPart1("./assets/input.txt");
  auto end1 = measure();
  logResult(result1, start1, end1);

  auto start2 = measure();
  auto result2 = runPart2("./assets/input.txt");
  auto end2 = measure();
  logResult(result2, start2, end2);

  return 0;
}
