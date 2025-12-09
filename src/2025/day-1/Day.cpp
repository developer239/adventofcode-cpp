#include <numeric>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

int runPart1(const std::string& filename) {
  const int dialMaximum = 100;
  int dialPointer = 50;
  int numberOfTimesDialIsPointingZero = 0;
  std::vector<int> safeInputs = {
      /*
      -68
      -30
      +48
      ...
      */
  };

  auto lines = ReadInput<std::string>(filename);
  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      const auto direction = lineValue.at(0);
      auto value = lineValue.substr(1, lineValue.length());
      auto numeric = std::stoi(value);

      switch (direction) {
        case 'L': {
          safeInputs.emplace_back(-numeric);
          break;
        }
        case 'R': {
          safeInputs.emplace_back(numeric);
          break;
        }
      }
    }
  }

  for (auto safeInput : safeInputs) {
    const auto result1 = dialPointer + safeInput % dialMaximum;
    const auto result2 = result1 % dialMaximum;

    dialPointer = result2 < 0 ? dialMaximum + result2 : result2;

    if (dialPointer == 0) {
      numberOfTimesDialIsPointingZero += 1;
    }
  }

  return numberOfTimesDialIsPointingZero;
}

int runPart2(const std::string& filename) {
  const int dialMaximum = 100;
  int dialPointer = 50;
  int numberOfTimesDialPassedZero = 0;
  std::vector<int> safeInputs = {
      /*
      -68
      -30
      +48
      ...
      */
  };

  auto lines = ReadInput<std::string>(filename);
  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      const auto direction = lineValue.at(0);
      auto value = lineValue.substr(1, lineValue.length());
      auto numeric = std::stoi(value);

      switch (direction) {
        case 'L': {
          safeInputs.emplace_back(-numeric);
          break;
        }
        case 'R': {
          safeInputs.emplace_back(numeric);
          break;
        }
      }
    }
  }

  for (auto safeInput : safeInputs) {
    const auto result1 = dialPointer + safeInput % dialMaximum;
    const auto result2 = result1 % dialMaximum;

    int a = (dialPointer + safeInput) / dialMaximum;
    numberOfTimesDialPassedZero += a;

    dialPointer = result2 < 0 ? dialMaximum + result2 : result2;
  }

  return numberOfTimesDialPassedZero;
}