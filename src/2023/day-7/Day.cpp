#include <functional>
#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

std::unordered_map<char, int> cardStrengthMap = {
    {'A', 14},
    {'K', 13},
    {'Q', 12},
    {'J', 11},
    {'T', 10},
    {'9', 9},
    {'8', 8},
    {'7', 7},
    {'6', 6},
    {'5', 5},
    {'4', 4},
    {'3', 3},
    {'2', 2}};

enum HandType {
  FIVE_KIND = 7,
  FOUR_KIND = 6,
  FULL_HOUSE = 5,
  THREE_KIND = 4,
  TWO_PAIR = 3,
  ONE_PAIR = 2,
  HIGH_CARD = 1,
};

// 32T3K 765
struct Hand {
  std::string cards;  // 32T3K
  int bid;            // 765
  HandType type;

  int GetCardStrengthAtPosition(int position) const {
    return cardStrengthMap[cards[position]];
  }

  bool operator<(const Hand& other) const {
    // Hands are primarily ordered based on type;
    auto isDifferentType = type != other.type;
    if (isDifferentType) {
      return type < other.type;
    }

    // If two hands have the same type, a second ordering rule takes effect.
    // Start by comparing the first card in each hand.
    for (int i = 0; i < cards.size(); i++) {
      auto cardStrength = GetCardStrengthAtPosition(i);
      auto otherCardStrength = other.GetCardStrengthAtPosition(i);

      if (cardStrength != otherCardStrength) {
        return cardStrength < otherCardStrength;
      }
    }

    return false;
  }
};

HandType GetHandType(std::string cards) {
  std::unordered_map<char, int> cardCountMap = {};
  for (auto& card : cards) {
    cardCountMap[card] += 1;
  }

  std::vector<int> sortedCardCounts = {};
  for (auto& cardCount : cardCountMap) {
    sortedCardCounts.push_back(cardCount.second);
  }
  std::sort(sortedCardCounts.begin(), sortedCardCounts.end(), std::greater<>());

  // five kind
  if (cardCountMap.size() == 1) {
    return FIVE_KIND;
  }

  // four kind of full house
  if (cardCountMap.size() == 2) {
    if (sortedCardCounts[0] == 4) {
      return FOUR_KIND;
    } else {
      return FULL_HOUSE;
    }
  }

  // three kind or two pair
  if (cardCountMap.size() == 3) {
    if (sortedCardCounts[0] == 3) {
      return THREE_KIND;
    } else {
      return TWO_PAIR;
    }
  }

  auto isOnePair = cardCountMap.size() == 4;
  if (isOnePair) {
    return ONE_PAIR;
  }

  return HIGH_CARD;
}

std::vector<Hand> ParseInput(const std::string& filename) {
  std::vector<Hand> result = {};

  auto lines = ReadInput<std::string>(filename);

  for (auto& line : lines) {
    auto parts = splitString(line.value(), ' ');

    auto cardType = GetHandType(parts[0]);

    result.push_back({parts[0], std::stoi(parts[1]), cardType});
  }

  return result;
}

bool compareHands(const Hand& a, const Hand& b) { return a < b; }

int runPart1(const std::string& filename) {
  auto input = ParseInput(filename);

  std::sort(input.begin(), input.end(), compareHands);

  int totalWinnings = 0;
  for (int i = 0; i < input.size(); i++) {
    auto rank = i + 1;
    totalWinnings += rank * input[i].bid;
  }

  for(auto& hand : input) {
    std::cout << hand.cards << " " << hand.bid << std::endl;
  }

  return totalWinnings;
}

int runPart2(const std::string& filename) { return 0; }
