#include <unordered_map>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

typedef enum {
  lose = 0,
  draw = 1,
  win = 2,
} GameResult;

typedef enum { rock = 0, paper = 1, scissors = 2 } Choice;

std::unordered_map<char, Choice> inputToChoice = {
    {'X', rock},
    {'A', rock},
    {'Y', paper},
    {'B', paper},
    {'Z', scissors},
    {'C', scissors},
};

int calculateChoiceScore(Choice yourChoice) { return yourChoice + 1; }

int calculatePlayScore(Choice yourChoice, Choice opponentChoice) {
  std::vector<std::vector<int>> scores{
      {draw, lose, win},  // rock against {rock, paper, scissors}
      {win, draw, lose},  // paper against {rock, paper, scissors}
      {lose, win, draw},  // scissors against {rock, paper, scissors}
  };

  return scores[yourChoice][opponentChoice] * 3;
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int score = 0;
  for (auto line : lines) {
    if (line.has_value()) {
      Choice yourChoice = inputToChoice[line.value()[2]];
      Choice opponentChoice = inputToChoice[line.value()[0]];

      auto playScore = calculatePlayScore(yourChoice, opponentChoice);
      auto choiceScore = calculateChoiceScore(yourChoice);

      score += playScore + choiceScore;
    }
  }

  return score;
}

std::unordered_map<char, GameResult> inputToRoundEndChoice = {
    {'X', lose},
    {'Y', draw},
    {'Z', win},
};

Choice findChoice(GameResult roundEndChoice, Choice opponentChoice) {
  std::vector<std::vector<int>> choices{
      {scissors, rock, paper},  // want to lose against {rock, paper, scissors}
      {rock, paper, scissors},  // want to draw against {rock, paper, scissors}
      {paper, scissors, rock},  // want to win against {rock, paper, scissors}
  };

  return static_cast<Choice>(choices[roundEndChoice][opponentChoice]);
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int score = 0;
  for (auto line : lines) {
    if (line.has_value()) {
      GameResult roundEndChoice = inputToRoundEndChoice[line.value()[2]];

      Choice opponentChoice = inputToChoice[line.value()[0]];
      Choice yourChoice = findChoice(roundEndChoice, opponentChoice);

      auto playScore = calculatePlayScore(yourChoice, opponentChoice);
      auto choiceScore = calculateChoiceScore(yourChoice);

      score += playScore + choiceScore;
    }
  }

  return score;
}
