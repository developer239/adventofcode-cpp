#include <gtest/gtest.h>

#include <fstream>

template<typename T>
  void logVectorLines(std::vector<T>& lines) {
    if constexpr (std::is_same_v<T, std::optional<int>>) {
      for (auto& line: lines) {
        if (line.has_value()) {
          std::cout << line.value() << std::endl;
        } else {
          std::cout << " " << std::endl;
        }
      }
    } else {
      for (auto& line: lines) {
        std::cout << line << std::endl;
      }
    }
  }

std::vector<std::optional<int>> readInput(const std::string& filename) {
  std::ifstream file(filename);
  std::vector<std::optional<int>> input;
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty()) {
      input.emplace_back(std::nullopt);
    } else {
      input.emplace_back(std::stoi(line));
    }
  }
  return input;
}

int countCaloriesPart1() {
  auto lines = readInput("../../../src/day-1/input.txt");

  std::cout << " " << std::endl;

  std::vector<int> sums = { 0 };

  for (auto line: lines) {
    if (line.has_value()) {
      auto lastIndex = sums.size() - 1;
      sums[lastIndex] += line.value();
    } else {
      sums.push_back(0);
    }
  }

  return *std::max_element(sums.begin(), sums.end());
}

TEST(TestCase, FailingTest) {
  EXPECT_EQ(1, countCaloriesPart1());
}
