#include <numeric>
#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

int runPart1(const std::string& filename) {
  auto result = 0;
  auto lines = ReadInput<std::string>(filename);

  std::vector<int> leftList = {};
  std::vector<int> rightList = {};
  std::vector<int> diffs = {};

  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      auto splitStringResult = splitString(lineValue, ' ');
      auto left = splitStringResult[0];
      auto right = splitStringResult[1];

      auto leftInt = std::stoi(left);
      auto rightInt = std::stoi(right);

      leftList.emplace_back(leftInt);
      rightList.emplace_back(rightInt);
    }
  }

  std::sort(leftList.begin(), leftList.end());
  std::sort(rightList.begin(), rightList.end());

  for (auto i = 0; i < leftList.size(); i++) {
    auto left = leftList[i];
    auto right = rightList[i];

    auto diff = std::abs(left - right);
    diffs.emplace_back(diff);
  }

  result = std::accumulate(diffs.begin(), diffs.end(), 0);

  return result;
}

int runPart2(const std::string& filename) {
  auto result = 0;
  auto lines = ReadInput<std::string>(filename);

  std::vector<int> leftList = {};
  std::vector<int> rightList = {};
  std::vector<int> similarityScores = {};

  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      auto splitStringResult = splitString(lineValue, ' ');
      auto left = splitStringResult[0];
      auto right = splitStringResult[1];

      auto leftInt = std::stoi(left);
      auto rightInt = std::stoi(right);

      leftList.emplace_back(leftInt);
      rightList.emplace_back(rightInt);
    }
  }

  for (auto i = 0; i < leftList.size(); i++) {
    auto left = leftList[i];
    auto count = 0;

    for (auto m = 0; m < rightList.size(); m++) {
      auto right = rightList[m];

      if(left == right) {
        count++;
      }
    }

    similarityScores.push_back(left * count);
  }

  result = std::accumulate(similarityScores.begin(), similarityScores.end(), 0);

  return result;
}
