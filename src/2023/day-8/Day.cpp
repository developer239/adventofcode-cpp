#include <numeric>
#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

struct Choice {
  std::string left;
  std::string right;
};

using Nodes = std::unordered_map<std::string, Choice>;
using Directions = std::vector<char>;

Directions directions = {};

struct Input {
  Nodes nodes;
  Directions directions;
};

Input ParseInput(const std::string& filename) {
  Input result = {};

  auto lines = ReadInput<std::string>(filename);

  auto lineWithDirections = lines[0];
  for (auto& c : lineWithDirections.value()) {
    result.directions.push_back(c);
  }

  for (long long i = 1; i < lines.size(); i++) {
    if (lines[i].has_value()) {
      auto line = lines[i].value();
      auto splitLine = splitString(line, '=');

      auto nodeKey = splitLine[0];

      auto nodeValue = splitLine[1];
      nodeValue = nodeValue.substr(1, nodeValue.size() - 2);
      auto splitNodeValue = splitString(nodeValue, ',');
      auto left = splitNodeValue[0];
      auto right = splitNodeValue[1];

      result.nodes[nodeKey].left = left;
      result.nodes[nodeKey].right = right;
    }
  }

  return result;
}

int runPart1(const std::string& filename) {
  auto input = ParseInput(filename);

  int stepCount = 0;
  auto currentNode = input.nodes["AAA"];
  for (int i = 0; i < input.directions.size(); i++) {
    stepCount += 1;
    auto direction = input.directions[i];

    auto targetNode = direction == 'L' ? currentNode.left : currentNode.right;
    currentNode = input.nodes[targetNode];

    if (targetNode != "ZZZ" && i + 1 == input.directions.size()) {
      i = -1;
    }
  }

  return stepCount;
}

int runPart2(const std::string& filename) { return 0; }
