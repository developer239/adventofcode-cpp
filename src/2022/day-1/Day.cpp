#include <vector>

#include "src/ReadInput.cpp"
#include "src/LogVectorLines.cpp"

int runPart1(const std::string& filename) {
  auto lines = ReadInput<int>(filename);

  std::vector<int> sums = {0};

  for (auto line : lines) {
    if (line.has_value()) {
      auto lastIndex = sums.size() - 1;
      sums[lastIndex] += line.value();
    } else {
      sums.push_back(0);
    }
  }

  return *std::max_element(sums.begin(), sums.end());
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<int>(filename);

  std::vector<int> sums = {0};

  for (auto line : lines) {
    if (line.has_value()) {
      auto lastIndex = sums.size() - 1;
      sums[lastIndex] += line.value();
    } else {
      sums.push_back(0);
    }
  }

  std::nth_element(sums.begin(), sums.begin() + 2, sums.end(), std::greater());

  return sums[0] + sums[1] + sums[2];
}
