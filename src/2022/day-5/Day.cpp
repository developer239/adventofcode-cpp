#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

std::string runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  std::vector<std::stack<char>> stacks;

  stacks.push_back(std::stack<char>());
  stacks[0].push('W');
  stacks[0].push('R');
  stacks[0].push('F');

  stacks.push_back(std::stack<char>());
  stacks[1].push('T');
  stacks[1].push('H');
  stacks[1].push('M');
  stacks[1].push('C');
  stacks[1].push('D');
  stacks[1].push('V');
  stacks[1].push('W');
  stacks[1].push('P');

  stacks.push_back(std::stack<char>());
  stacks[2].push('P');
  stacks[2].push('M');
  stacks[2].push('Z');
  stacks[2].push('N');
  stacks[2].push('L');

  stacks.push_back(std::stack<char>());
  stacks[3].push('J');
  stacks[3].push('C');
  stacks[3].push('H');
  stacks[3].push('R');

  stacks.push_back(std::stack<char>());
  stacks[4].push('C');
  stacks[4].push('P');
  stacks[4].push('G');
  stacks[4].push('H');
  stacks[4].push('Q');
  stacks[4].push('T');
  stacks[4].push('B');

  stacks.push_back(std::stack<char>());
  stacks[5].push('G');
  stacks[5].push('C');
  stacks[5].push('W');
  stacks[5].push('L');
  stacks[5].push('F');
  stacks[5].push('Z');

  stacks.push_back(std::stack<char>());
  stacks[6].push('W');
  stacks[6].push('V');
  stacks[6].push('L');
  stacks[6].push('Q');
  stacks[6].push('Z');
  stacks[6].push('J');
  stacks[6].push('G');
  stacks[6].push('C');

  stacks.push_back(std::stack<char>());
  stacks[7].push('P');
  stacks[7].push('N');
  stacks[7].push('R');
  stacks[7].push('F');
  stacks[7].push('W');
  stacks[7].push('T');
  stacks[7].push('V');
  stacks[7].push('C');

  stacks.push_back(std::stack<char>());
  stacks[8].push('J');
  stacks[8].push('W');
  stacks[8].push('H');
  stacks[8].push('G');
  stacks[8].push('R');
  stacks[8].push('S');
  stacks[8].push('V');

  for (auto line : lines) {
    if (line.has_value()) {
      int count, fromIndex, toIndex;
      sscanf(
          line.value().c_str(),
          "move %d from %d to %d",
          &count,
          &fromIndex,
          &toIndex
      );
      fromIndex--;
      toIndex--;

      std::vector<char> toMove;
      for (int i = 0; i < count; i++) {
        toMove.push_back(stacks[fromIndex].top());
        stacks[fromIndex].pop();
      }

      for (int i = toMove.size() - 1; i >= 0; i--) {
        stacks[toIndex].push(toMove[i]);
      }
    }
  }

  std::string result = "";

  for (auto stack : stacks) {
    if (!stack.empty()) {
      result += stack.top();
    }
  }

  return result;
}
