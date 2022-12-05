#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

std::string runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  std::vector<std::stack<char>> stacks;

  stacks.push_back(std::stack<char>());
  stacks[0].push('Z');
  stacks[0].push('N');

  stacks.push_back(std::stack<char>());
  stacks[1].push('M');
  stacks[1].push('C');
  stacks[1].push('D');

  stacks.push_back(std::stack<char>());
  stacks[2].push('P');

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

      std::cout << count;
      std::cout << fromIndex;
      std::cout << toIndex << std::endl;

      for(int i = 0; i < count; i++) {
        stacks[toIndex].push(stacks[fromIndex].top());
        stacks[fromIndex].pop();
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
