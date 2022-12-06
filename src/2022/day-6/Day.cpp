#include <unordered_map>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

int rollingWindowUniqString(const std::string& input, int length) {
  std::string rollingWindow;
  int currentIndex = 0;
  while (currentIndex + length < input.size()) {
    rollingWindow = input.substr(currentIndex, length);

    std::unordered_map<char, int> letters;
    for (auto letter : rollingWindow) {
      if (letters[letter]) {
        letters[letter] += 1;
      } else {
        letters[letter] = 1;
      }
    }

    bool shouldContinue = false;
    for (auto letter : letters) {
      if (letter.second > 1) {
        currentIndex += 1;
        shouldContinue = true;
      }
    }

    if (shouldContinue) {
      continue;
    }

    break;
  }

  return currentIndex + length;
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  return rollingWindowUniqString(lines[0].value(), 4);
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  return rollingWindowUniqString(lines[0].value(), 14);
}
