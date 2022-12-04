#include <unordered_map>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

int asciiLetterToNumber(char letter) {
  if (letter >= 'a' && letter <= 'z') {
    return letter - 96;
  } else {
    return letter - 38;
  }
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  int sum = 0;

  for (auto line: lines) {
    if (line.has_value()) {
      std::unordered_map<char, int> itemsInRucksack = {};
      int length = line.value().length();
      int half = length / 2;

      for (int i = 0; i < length; i++) {
        auto item = line.value()[i];

        if (i < half) {
          itemsInRucksack[item] = 1;
        } else {
          if (itemsInRucksack[item]) {
            sum += asciiLetterToNumber(item);
            break;
          }
        }
      }
    }
  }

  return sum;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int sum = 0;

  std::unordered_map<char, int> uniqItemsPerGroup = {};
  for (int lineNumber = 0; lineNumber < lines.size(); lineNumber++) {
    std::unordered_map<char, int> uniqItemsPerElf = {};
    auto line = lines[lineNumber];

    if (line.has_value()) {
      if (lineNumber % 3 == 0) {
        uniqItemsPerGroup.clear();
      }

      for (char item: line.value()) {
        if (uniqItemsPerElf[item]) {
          uniqItemsPerElf[item] = 1;
        }
      }

      for (auto item: uniqItemsPerElf) {
        if (uniqItemsPerGroup[item.first]) {
          uniqItemsPerGroup[item.first] += 1;

          if (uniqItemsPerGroup[item.first] == 3) {
            sum += asciiLetterToNumber(item.first);
          }
        } else {
          uniqItemsPerGroup[item.first] = 1;
        }
      }
    }
  }

  return sum;
}
