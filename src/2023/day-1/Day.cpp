#include <numeric>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

int runPart1(const std::string& filename) {
  auto result = 0;
  auto lines = ReadInput<int>(filename);

  for (auto line : lines) {
    if (line.has_value()) {
      // auto value = line.value();
    }
  }

  return result;
}

int runPart2(const std::string& filename) {
  auto result = 0;
  auto lines = ReadInput<int>(filename);

  for (auto line : lines) {
    if (line.has_value()) {
      // auto value = line.value();
    }
  }

  return result;
}
