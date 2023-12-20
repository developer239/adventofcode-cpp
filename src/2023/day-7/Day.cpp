#include <functional>
#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

std::unordered_map<char, int> cardStrengthMap = {
    {'A', 14},
    {'K', 13},
    {'Q', 12},
    // part 1
    // {'J', 11},
    {'T', 10},
    {'9', 9},
    {'8', 8},
    {'7', 7},
    {'6', 6},
    {'5', 5},
    {'4', 4},
    {'3', 3},
    {'2', 2},
    {'J', 1}};

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
  std::unordered_map<char, int> cardCountMap;
  int jokerCount = 0;

  for (char card : cards) {
    if (card == 'J') {
      jokerCount++;
    } else {
      cardCountMap[card]++;
    }
  }

  // Adjust counts with Joker
  if (jokerCount > 0) {
    if (!cardCountMap.empty()) {
      auto it = std::max_element(cardCountMap.begin(), cardCountMap.end(),
                                 [](const auto& p1, const auto& p2) {
                                   return p1.second < p2.second;
                                 });
      it->second += jokerCount;
    } else {
      // All cards are Jokers
      return FIVE_KIND;
    }
  }

  std::vector<int> counts;
  for (auto& p : cardCountMap) {
    counts.push_back(p.second);
  }
  std::sort(counts.begin(), counts.end(), std::greater<int>());

  if (counts[0] == 5) return FIVE_KIND;
  if (counts[0] == 4) return FOUR_KIND;
  if (counts.size() == 2 && counts[1] == 2) return FULL_HOUSE;
  if (counts[0] == 3) return THREE_KIND;
  if (counts.size() >= 3 && counts[1] == 2) return TWO_PAIR;
  if (counts.size() >= 4 && counts[0] == 2) return ONE_PAIR;

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

int runPart2(const std::string& filename) {
  auto input = ParseInput(filename);

  std::sort(input.begin(), input.end(), compareHands);

  int totalWinnings = 0;
  for (int i = 0; i < input.size(); i++) {
    auto rank = i + 1;
    totalWinnings += rank * input[i].bid;
  }

  for (auto& hand : input) {
    std::cout << hand.cards << " " << hand.bid << std::endl;
  }

  return totalWinnings;
}
