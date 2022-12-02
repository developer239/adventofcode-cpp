#include <unordered_map>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

typedef enum { rock = 0, paper = 1, scissors = 2 } ChoiceType;

std::unordered_map<char, ChoiceType> inputToChoiceType = {
    {'X', rock},
    {'A', rock},
    {'Y', paper},
    {'B', paper},
    {'Z', scissors},
    {'C', scissors},
};

int calculateChoiceScore(ChoiceType yourChoice) {
  switch (yourChoice) {
    case rock:
      return 1;
    case paper:
      return 2;
    case scissors:
      return 3;
  }
}

int calculatePlayScore(ChoiceType yourChoice, ChoiceType opponentChoice) {
  std::vector<std::vector<int>> scores {
      {3, 0, 6},
      {6, 3, 0},
      {0, 6, 3},
  };

  return scores[yourChoice][opponentChoice];
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int score = 0;
  for (auto line : lines) {
    if (line.has_value()) {
      ChoiceType yourChoice = inputToChoiceType[line.value()[2]];
      ChoiceType opponentChoice = inputToChoiceType[line.value()[0]];

      auto playScore = calculatePlayScore(yourChoice, opponentChoice);
      auto choiceScore = calculateChoiceScore(yourChoice);

      score += playScore + choiceScore;
    }
  }

  return score;
}

typedef enum {
  lose = 0,
  draw = 1,
  win = 2,
} RoundEndChoice;

std::unordered_map<char, RoundEndChoice> inputToRoundEndChoice = {
    {'X', lose},
    {'Y', draw},
    {'Z', win},
};

ChoiceType findChoice(RoundEndChoice roundEndChoice, ChoiceType opponentChoice) {
  std::vector<std::vector<int>> choices {
      {2, 0, 1}, // win
      {0, 1, 2}, // draw
      {1, 2, 0}, // lose
  };

  return static_cast<ChoiceType>(choices[roundEndChoice][opponentChoice]);
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int score = 0;
  for (auto line : lines) {
    if (line.has_value()) {
      RoundEndChoice roundEndChoice = inputToRoundEndChoice[line.value()[2]];

      ChoiceType opponentChoice = inputToChoiceType[line.value()[0]];
      ChoiceType yourChoice = findChoice(roundEndChoice, opponentChoice);

      auto playScore = calculatePlayScore(yourChoice, opponentChoice);
      auto choiceScore = calculateChoiceScore(yourChoice);

      score += playScore + choiceScore;
    }
  }

  return score;
}
