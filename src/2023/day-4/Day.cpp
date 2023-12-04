#include <functional>
#include <numeric>
#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

int CalculateMatchValue(int numMatches) {
  if (numMatches == 0) {
    return 0;
  }

  if (numMatches == 1) {
    return 1;
  }

  int value = 1;
  for (int i = 1; i < numMatches; i++) {
    value *= 2;
  }

  return value;
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  auto score = 0;

  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
      auto gameData = splitString(lineValue, ':');
      auto gameId = splitString(gameData[0], ' ')[1];

      auto myNumbersString = splitString(gameData[1], '|')[0];
      auto winningNumbersString = splitString(gameData[1], '|')[1];

      auto myNumbers = splitString(myNumbersString, ' ');
      auto winningNumbers = splitString(winningNumbersString, ' ');

      int numMatches = 0;
      for (const auto& myNumber : myNumbers) {
        for (const auto& winningNumber : winningNumbers) {
          if (myNumber == winningNumber) {
            numMatches += 1;
          }
        }
      }

      int matchValue = CalculateMatchValue(numMatches);
      score += matchValue;
    }
  }

  return score;
}

int GetCardNumberFromLine(const std::string& line) {
  // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
  auto gameData = splitString(line, ':');
  auto gameId = splitString(gameData[0], ' ')[1];

  return std::stoi(gameId);
}

struct CardInformation {
  int count;
  int cardNumber;
};

using CardInformationMap = std::unordered_map<std::string, CardInformation>;

int CheckCardWinningNumbers(
    int cardNumber, std::vector<std::optional<std::string>> lines,
    CardInformationMap& cardInformationMap
) {
  std::cout << "Checking card: " << cardNumber << std::endl;

  auto cardIndex = cardNumber - 1;

  if (lines[cardIndex].has_value()) {
    auto lineValue = lines[cardIndex].value();

    // Card 1: 41 48 83 86 17 | 83 86  6 31 17  9 48 53
    auto gameData = splitString(lineValue, ':');

    auto myNumbersString = splitString(gameData[1], '|')[0];
    auto winningNumbersString = splitString(gameData[1], '|')[1];

    auto myNumbers = splitString(myNumbersString, ' ');
    auto winningNumbers = splitString(winningNumbersString, ' ');

    std::string cardNumberStr = std::to_string(cardNumber);
    cardInformationMap[cardNumberStr].count += 1;
    cardInformationMap[cardNumberStr].cardNumber = cardNumber;

    int numMatches = 0;
    for (const auto& myNumber : myNumbers) {
      for (const auto& winningNumber : winningNumbers) {
        if (myNumber == winningNumber) {
          numMatches += 1;
        }
      }
    }

    for (int nextCard = cardNumber + 1; nextCard <= cardNumber + numMatches;
         nextCard++) {
      CheckCardWinningNumbers(nextCard, lines, cardInformationMap);
    }

    return numMatches;
  }

  return 0;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  CardInformationMap cardsInfo = {};

  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      auto cardNumber = GetCardNumberFromLine(lineValue);
      CheckCardWinningNumbers(cardNumber, lines, cardsInfo);
    }
  }

  int score = 0;
  std::accumulate(
      cardsInfo.begin(),
      cardsInfo.end(),
      0,
      [&score](int acc, const auto& cardInfo) {
        score += cardInfo.second.count;
        return acc;
      }
  );

  return score;
}
