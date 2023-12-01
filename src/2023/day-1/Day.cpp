#include <numeric>
#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

int runPart1(const std::string& filename) {
  auto result = 0;
  auto lines = ReadInput<std::string>(filename);

  for (auto line : lines) {
    if (line.has_value()) {
      auto calibrationValue = line.value();

      int firstNumber = 0;
      int secondNumber = 0;

      for (int i = 0; i < calibrationValue.length(); i++) {
        auto letter = calibrationValue[i];

        if (std::isdigit(letter)) {
          int letterInt = letter - '0';

          if (!firstNumber) {
            firstNumber = letterInt;
          } else {
            secondNumber = letterInt;
          }
        }
      }

      if(!secondNumber) {
        secondNumber = firstNumber;
      }

      auto total = firstNumber * 10 + secondNumber;
      result += total;
    }
  }

  return result;
}

std::unordered_map<std::string, int> stringToIntMap = {
    {"one", 1},
    {"two", 2},
    {"three", 3},
    {"four", 4},
    {"five", 5},
    {"six", 6},
    {"seven", 7},
    {"eight", 8},
    {"nine", 9},
};

int runPart2(const std::string& filename) {
  auto result = 0;
  auto lines = ReadInput<std::string>(filename);

  for (auto line : lines) {
    if (line.has_value()) {
      std::string numberAsString = "";
      auto calibrationValue = line.value();

      std::vector<int> digits = {};

      for (int i = 0; i < calibrationValue.length(); i++) {
        auto letter = calibrationValue[i];

        if (std::isdigit(letter)) {
          int letterInt = letter - '0';

          digits.push_back(letterInt);
          numberAsString = "";
        } else {
          numberAsString.push_back(letter);
        }

        for (int j = 0; j < numberAsString.length(); j++) {
          auto slicedNumberAsString = numberAsString.substr(j, numberAsString.length());

          auto stringNumberToInt = stringToIntMap[slicedNumberAsString];
          if(stringNumberToInt) {
            digits.push_back(stringNumberToInt);
            break;
          }
        }
      }

      auto firstNumber = digits.front();
      auto secondNumber = digits.back();

      auto total = firstNumber * 10 + secondNumber;
      result += total;
    }
  }

  return result;
}
