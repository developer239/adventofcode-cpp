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

      int tensCount = 0;
      int onesCount = 0;

      for (int i = 0; i < calibrationValue.length(); i++) {
        auto letter = calibrationValue[i];

        if (std::isdigit(letter)) {
          int digit = letter - '0';

          if (!tensCount) {
            tensCount = digit;
          } else {
            onesCount = digit;
          }
        }
      }

      if(!onesCount) {
        onesCount = tensCount;
      }

      auto total = tensCount * 10 + onesCount;
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
      std::string digitAsWord = "";
      auto calibrationValue = line.value();

      std::vector<int> digits = {};

      for (int i = 0; i < calibrationValue.length(); i++) {
        auto letter = calibrationValue[i];

        if (std::isdigit(letter)) {
          int letterInt = letter - '0';

          digits.push_back(letterInt);
          digitAsWord = "";
        } else {
          digitAsWord.push_back(letter);
        }

        // look for digit (represented as word) at the end of the string
        for (int sliceIndexAt = 0; sliceIndexAt < digitAsWord.length();
             sliceIndexAt++) {
          auto slicedEnd =
              digitAsWord.substr(sliceIndexAt, digitAsWord.length());

          auto stringNumberToInt = stringToIntMap[slicedEnd];
          if(stringNumberToInt) {
            digits.push_back(stringNumberToInt);
            break;
          }
        }
      }

      auto tensCount = digits.front();
      auto onesCount = digits.back();

      auto total = tensCount * 10 + onesCount;
      result += total;
    }
  }

  return result;
}
