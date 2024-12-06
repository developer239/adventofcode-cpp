#include <map>
#include <set>
#include <tuple>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

int runPart1(const std::string& filename) {
  auto input = ReadInput<std::string>(filename);
  std::vector<std::string> map;

  for (const auto& line : input) {
    if (line) {
      map.push_back(line.value());
    }
  }

  int currentX = 0;
  int currentY = 0;
  std::string facing = "up";

  for (int yToFind = 0; yToFind < map.size(); yToFind++) {
    for (int xToFind = 0; xToFind < map[yToFind].size(); xToFind++) {
      auto letter = map[yToFind][xToFind];
      if (letter == '^') {
        currentX = xToFind;
        currentY = yToFind;
        map[currentY][currentX] = '.';
      }
    }
  }

  std::map<std::string, std::pair<int, int>> moves =
      {{"up", {0, -1}}, {"right", {1, 0}}, {"down", {0, 1}}, {"left", {-1, 0}}};

  std::map<std::string, std::string> turnRight =
      {{"up", "right"}, {"right", "down"}, {"down", "left"}, {"left", "up"}};

  std::set<std::pair<int, int>> visitedPositions;
  visitedPositions.insert({currentX, currentY});

  bool isInsideMap = true;
  while (isInsideMap) {
    auto [moveX, moveY] = moves[facing];
    int nextX = currentX + moveX;
    int nextY = currentY + moveY;

    if (nextX < 0 || nextX >= map[0].size() || nextY < 0 ||
        nextY >= map.size()) {
      if (map[currentY][currentX] != '#') {
        visitedPositions.insert({currentX, currentY});
        isInsideMap = false;
      }
      facing = turnRight[facing];
    }

    else if (map[nextY][nextX] == '#') {
      facing = turnRight[facing];
    } else {
      currentX = nextX;
      currentY = nextY;
      visitedPositions.insert({currentX, currentY});
    }
  }

  return visitedPositions.size();
}

int runPart2(const std::string& filename) {
  auto input = ReadInput<std::string>(filename);
  std::vector<std::string> map;

  for (const auto& line : input) {
    if (line) {
      map.push_back(line.value());
    }
  }

  int startX = 0;
  int startY = 0;
  for (int yToFind = 0; yToFind < map.size(); yToFind++) {
    for (int xToFind = 0; xToFind < map[yToFind].size(); xToFind++) {
      if (map[yToFind][xToFind] == '^') {
        startX = xToFind;
        startY = yToFind;
        map[startY][startX] = '.';
      }
    }
  }

  std::map<std::string, std::pair<int, int>> moves =
      {{"up", {0, -1}}, {"right", {1, 0}}, {"down", {0, 1}}, {"left", {-1, 0}}};

  std::map<std::string, std::string> turnRight =
      {{"up", "right"}, {"right", "down"}, {"down", "left"}, {"left", "up"}};

  int loopCount = 0;

  for (int yToTry = 0; yToTry < map.size(); yToTry++) {
    for (int xToTry = 0; xToTry < map[0].size(); xToTry++) {
      if (map[yToTry][xToTry] == '#' ||
          (xToTry == startX && yToTry == startY)) {
        continue;
      }

      auto testMap = map;
      testMap[yToTry][xToTry] = '#';

      int currentX = startX;
      int currentY = startY;
      std::string facing = "up";

      std::set<std::tuple<int, int, std::string>> visitedStates;
      bool isInsideMap = true;
      bool hasFoundLoop = false;

      while (isInsideMap && !hasFoundLoop) {
        auto currentState = std::make_tuple(currentX, currentY, facing);

        if (visitedStates.count(currentState) > 0) {
          hasFoundLoop = true;
          break;
        }

        visitedStates.insert(currentState);

        auto [moveX, moveY] = moves[facing];
        int nextX = currentX + moveX;
        int nextY = currentY + moveY;

        if (nextX < 0 || nextX >= testMap[0].size() || nextY < 0 ||
            nextY >= testMap.size()) {
          if (testMap[currentY][currentX] != '#') {
            isInsideMap = false;
          }
          facing = turnRight[facing];
        } else if (testMap[nextY][nextX] == '#') {
          facing = turnRight[facing];
        } else {
          currentX = nextX;
          currentY = nextY;
        }
      }

      if (hasFoundLoop) {
        loopCount++;
      }
    }
  }

  return loopCount;
}
