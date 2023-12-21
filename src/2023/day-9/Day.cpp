#include <numeric>

#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

using SensorHistory = std::vector<std::vector<int>>;

SensorHistory ParseInput(const std::string& filename) {
  SensorHistory result = {};

  auto lines = ReadInput<std::string>(filename);

  for (auto& line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();
      std::vector<int> lineResult = {};

      auto splitLine = splitString(lineValue, ' ');
      for (auto& splitLinePart : splitLine) {
        lineResult.push_back({std::stoi(splitLinePart)});
      }
      result.push_back(lineResult);
    }
  }

  return result;
}

int runPart1(const std::string& filename) {
  auto history = ParseInput(filename);

  std::vector<int> predictedValues = {};

  //    3   3   3   3   3
  //      0   0   0   0
  for (int i = 0; i < history.size(); i++) {
    //  0   3   6   9  12  15
    auto& line = history[i];

    //  0   3   6   9  12  15
    //    3   3   3   3   3
    //      0   0   0   0
    std::vector<std::vector<int>> pyramid = {line};
    auto currentPyramidLine = line;
    bool allZeroes = std::all_of(
        currentPyramidLine.begin(),
        currentPyramidLine.end(),
        [](int i) { return i == 0; }
    );

    while (!allZeroes) {
      std::vector<int> nextLine = {};

      for (int j = 0; j < currentPyramidLine.size() - 1; j += 1) {
        auto left = currentPyramidLine[j];
        auto right = currentPyramidLine[j + 1];

        nextLine.push_back({right - left});
      }

      pyramid.push_back(nextLine);
      currentPyramidLine = nextLine;
      allZeroes = std::all_of(
          currentPyramidLine.begin(),
          currentPyramidLine.end(),
          [](int i) { return i == 0; }
      );
    }

    //    0   3   6   9  12  15   B
    //      3   3   3   3   3   A
    //        0   0   0   0   0
    auto pyramidWithPredictedValues = pyramid;
    // loop bottom up add last value on current line with last value on previous
    // line
    for (int j = pyramid.size() - 1; j > 0; j -= 1) {
      auto& currentLine = pyramid[j];
      auto& previousLine = pyramid[j - 1];

      auto lastValueCurrentLine = currentLine[currentLine.size() - 1];
      auto lastValuePreviousLine = previousLine[previousLine.size() - 1];

      previousLine.push_back({lastValueCurrentLine + lastValuePreviousLine});
      pyramidWithPredictedValues[j - 1] = previousLine;
    }

    auto firstLinePyramidWithPredictedValues = pyramidWithPredictedValues[0];
    auto predictedValue = firstLinePyramidWithPredictedValues
        [firstLinePyramidWithPredictedValues.size() - 1];

    predictedValues.push_back(predictedValue);
  }

  auto predictedValuesSum =
      std::accumulate(predictedValues.begin(), predictedValues.end(), 0);

  return predictedValuesSum;
}

int runPart2(const std::string& filename) {
  auto history = ParseInput(filename);

  std::vector<int> predictedValues = {};

  //    3   3   3   3   3
  //      0   0   0   0
  for (int i = 0; i < history.size(); i++) {
    //  0   3   6   9  12  15
    auto& line = history[i];

    //  0   3   6   9  12  15
    //    3   3   3   3   3
    //      0   0   0   0
    std::vector<std::vector<int>> pyramid = {line};
    auto currentPyramidLine = line;
    bool allZeroes = std::all_of(
        currentPyramidLine.begin(),
        currentPyramidLine.end(),
        [](int i) { return i == 0; }
    );

    while (!allZeroes) {
      std::vector<int> nextLine = {};

      for (int j = 0; j < currentPyramidLine.size() - 1; j += 1) {
        auto left = currentPyramidLine[j];
        auto right = currentPyramidLine[j + 1];

        nextLine.push_back({right - left});
      }

      pyramid.push_back(nextLine);
      currentPyramidLine = nextLine;
      allZeroes = std::all_of(
          currentPyramidLine.begin(),
          currentPyramidLine.end(),
          [](int i) { return i == 0; }
      );
    }

    //    0   3   6   9  12  15   B
    //      3   3   3   3   3   A
    //        0   0   0   0   0
    auto pyramidWithPredictedValues = pyramid;
    // loop bottom up add last value on current line with last value on previous
    // line
    for (int j = pyramid.size() - 1; j > 0; j -= 1) {
      auto& currentLine = pyramid[j];
      auto& previousLine = pyramid[j - 1];

      auto firstValueCurrentLine = currentLine[0];
      auto firstValuePreviousLine = previousLine[0];

      previousLine.insert(
          previousLine.begin(),
          {firstValuePreviousLine - firstValueCurrentLine}
      );
      pyramidWithPredictedValues[j - 1] = previousLine;
    }

    auto firstLinePyramidWithPredictedValues = pyramidWithPredictedValues[0];
    auto predictedValue = firstLinePyramidWithPredictedValues[0];

    predictedValues.push_back(predictedValue);
  }

  auto predictedValuesSum =
      std::accumulate(predictedValues.begin(), predictedValues.end(), 0);

  return predictedValuesSum;
}
