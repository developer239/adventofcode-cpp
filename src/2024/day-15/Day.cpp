#include <map>
#include <tuple>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

std::map<std::string, std::tuple<int, int>> directions = {
    {"^", std::make_tuple(-1, 0)},
    {"v", std::make_tuple(1, 0)},
    {"<", std::make_tuple(0, -1)},
    {">", std::make_tuple(0, 1)},
};

void loadInstructions(
    int mapEndIndex, const std::vector<std::optional<std::string>>& input,
    std::vector<std::string>& instructions
) {
  for (int i = mapEndIndex; i < input.size(); i++) {
    if (!input[i].has_value()) {
      return;
    }
    auto line = input[i].value();
    for (int j = 0; j < line.size(); j++) {
      instructions.push_back(std::string(1, line[j]));
    }
  }
}

int loadMap(
    const std::vector<std::optional<std::string>>& input,
    std::vector<std::vector<std::string>>& map
) {
  for (int i = 0; i < input.size(); i++) {
    if (!input[i].has_value()) {
      return i + 1;
    }
    auto line = input[i].value();

    std::vector<std::string> row = {};
    for (int j = 0; j < line.size(); j++) {
      row.push_back(std::string(1, line[j]));
    }
    map.push_back(row);
  }

  return -1;
}

void loadInput(
    const std::string& filename, std::vector<std::vector<std::string>>& map,
    std::vector<std::string>& instructions
) {
  auto input = ReadInput<std::string>(filename);
  auto mapEndIndex = loadMap(input, map);
  loadInstructions(mapEndIndex, input, instructions);
}

void printMap(const std::vector<std::vector<std::string>>& map) {
  for (auto row : map) {
    for (auto col : row) {
      std::cout << col;
    }
    std::cout << std::endl;
  }
}

std::tuple<int, int> findRobotPosition(
    const std::vector<std::vector<std::string>>& map
) {
  for (auto i = 0; i < map.size(); i++) {
    for (auto j = 0; j < map[i].size(); j++) {
      if (map[i][j] == "@") {
        return std::make_tuple(i, j);
      }
    }
  }

  return std::make_tuple(-1, -1);
}

bool canMove(
    const std::vector<std::vector<std::string>>& map,
    const std::tuple<int, int>& direction
) {
  auto robotPosition = findRobotPosition(map);
  while (true) {
    auto row = std::get<0>(robotPosition);
    auto col = std::get<1>(robotPosition);
    auto rowDirection = std::get<0>(direction);
    auto colDirection = std::get<1>(direction);

    auto currentValue = map[row][col];
    if (currentValue == "#") {
      return false;
    }

    if (currentValue == ".") {
      return true;
    }

    robotPosition = std::make_tuple(row + rowDirection, col + colDirection);
  }
}

void move(
    std::vector<std::vector<std::string>>& map,
    const std::tuple<int, int>& direction
) {
  auto isAbleToMove = canMove(map, direction);
  if (isAbleToMove) {
    auto robotPosition = findRobotPosition(map);
    auto row = std::get<0>(robotPosition);
    auto col = std::get<1>(robotPosition);
    auto rowDirection = std::get<0>(direction);
    auto colDirection = std::get<1>(direction);

    // flag that we need to move boxes
    auto nextValue = map[row + rowDirection][col + colDirection];
    auto shouldMoveBox = nextValue == "O";

    // find last box in direction of travel
    if (shouldMoveBox) {
      for (int boxRow = row + rowDirection, boxCol = col + colDirection;
           boxRow < map.size() && boxCol < map[boxRow].size();
           boxRow += rowDirection, boxCol += colDirection) {
        if (map[boxRow + rowDirection][boxCol + colDirection] == "." ||
            map[boxRow + rowDirection][boxCol + colDirection] == "#") {
          map[boxRow + rowDirection][boxCol + colDirection] = "O";
          break;
        }
      }
    }

    // move robot
    map[row][col] = ".";
    map[row + rowDirection][col + colDirection] = "@";
  }
}

int sumAllBoxes(const std::vector<std::vector<std::string>>& map) {
  auto sum = 0;
  for(int row = 0; row < map.size(); row++) {
    for(int col = 0; col < map[0].size(); col++) {
      if (map[row][col] == "O") {
        sum += 100 * row + col;
      }
    }
  }

  return sum;
}

int runPart1(const std::string& filename) {
  std::vector<std::vector<std::string>> map = {};
  std::vector<std::string> instructions = {};

  loadInput(filename, map, instructions);

  for (std::string instruction : instructions) {
    auto direction = directions[instruction];
//    std::cout << std::endl;
//    std::cout << "Moving " << "\"" << instruction << "\"" << std::endl;
    move(map, direction);
//    printMap(map);
  }

  return sumAllBoxes(map);
}

int runPart2(const std::string& filename) { return 0; }
