#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

struct Metadata {
  int startAtLine;
  std::vector<std::stack<char>> stacks;
};

Metadata ParseInput(std::vector<std::optional<std::string>> lines) {
  int stackHeight = 0;
  for (const auto& line : lines) {
    if (line.has_value()) {
      stackHeight++;
    } else {
      stackHeight--;
      break;
    }
  }

  std::vector<std::stack<char>> stacks;
  int columnIndex = 0;
  int columnPosition = 1;
  int spaceBetween = 4;
  bool isColumnAtIndex = true;

  while (isColumnAtIndex) {
    stacks.emplace_back(std::stack<char>());

    for (int lineIndex = stackHeight - 1; lineIndex >= 0; lineIndex--) {
      auto line = lines[lineIndex];
      if (line.has_value()) {
        auto columnValue = line.value()[columnPosition];

        if (columnValue >= 'A' && columnValue <= 'Z') {
          stacks[columnIndex].push(columnValue);
        }
      }
    }

    columnIndex++;
    columnPosition += spaceBetween;
    isColumnAtIndex = columnPosition <= lines[stackHeight].value().size();
  }

  // add + 1 for index + 1 for the empty line
  return Metadata{stackHeight + 2, stacks};
}

std::string runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  auto metadata = ParseInput(lines);

  for (int index = metadata.startAtLine; index < lines.size(); index++) {
    auto line = lines[index];
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

      for (int i = 0; i < count; i++) {
        metadata.stacks[toIndex].push(metadata.stacks[fromIndex].top());
        metadata.stacks[fromIndex].pop();
      }
    }
  }

  std::string result = "";

  for (auto stack : metadata.stacks) {
    if (!stack.empty()) {
      result += stack.top();
    }
  }

  return result;
}

std::string runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  auto metadata = ParseInput(lines);

  for (int index = metadata.startAtLine; index < lines.size(); index++) {
    auto line = lines[index];
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

      std::stack<char> tempStack;
      for (int i = 0; i < count; i++) {
        tempStack.push(metadata.stacks[fromIndex].top());
        metadata.stacks[fromIndex].pop();
      }

      while (!tempStack.empty()) {
        metadata.stacks[toIndex].push(tempStack.top());
        tempStack.pop();
      }
    }
  }

  std::string result = "";

  for (auto stack : metadata.stacks) {
    if (!stack.empty()) {
      result += stack.top();
    }
  }

  return result;
}
