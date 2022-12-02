#include <unordered_map>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

typedef enum { rock = 'R', paper = 'P', scissors = 'S' } ChoiceType;

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
  switch (yourChoice) {
    case rock:
      switch (opponentChoice) {
        case rock:
          return 3;
        case paper:
          return 0;
        case scissors:
          return 6;
      }
      break;
    case paper:
      switch (opponentChoice) {
        case rock:
          return 6;
        case paper:
          return 3;
        case scissors:
          return 0;
      }
      break;
    case scissors:
      switch (opponentChoice) {
        case rock:
          return 0;
        case paper:
          return 6;
        case scissors:
          return 3;
      }
      break;
  }
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
