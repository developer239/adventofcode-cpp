#include <numeric>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

int runPart1(const std::string& filename) {
  auto lines = ReadInput<int>(filename);

  int increaseCount = 0;
  int previousHeight = 0;

  for (auto line : lines) {
    if (line.has_value()) {
      if (previousHeight == 0) {
        previousHeight = line.value();
        continue;
      }

      if (previousHeight < line.value()) {
        increaseCount++;
      }

      previousHeight = line.value();
    }
  }

  return increaseCount;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<int>(filename);

  int increaseCount = 0;

  std::vector leftWindow = std::vector<int>();
  std::vector rightWindow = std::vector<int>();

  int prevValue = 0;

  for (auto line : lines) {
    if (line.has_value()) {
      leftWindow.emplace_back(line.value());

      if(leftWindow.size() > 1) {
        rightWindow.emplace_back(prevValue);
      }

      if (leftWindow.size() > 3) {
        leftWindow.erase(leftWindow.begin());
      }

      if(rightWindow.size() > 3) {
        rightWindow.erase(rightWindow.begin());
      }

      if(leftWindow.size() == 3 && rightWindow.size() == 3) {
        auto leftSum = std::accumulate(leftWindow.begin(), leftWindow.end(), 0);
        auto rightSum = std::accumulate(rightWindow.begin(), rightWindow.end(), 0);

        if(leftSum > rightSum) {
          increaseCount++;
        }
      }

      prevValue = line.value();
    }
  }

  return increaseCount;
}
