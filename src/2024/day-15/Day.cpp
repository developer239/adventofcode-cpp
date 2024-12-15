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
  for (int row = 0; row < map.size(); row++) {
    for (int col = 0; col < map[0].size(); col++) {
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
    std::cout << std::endl;
    std::cout << "Moving " << "\"" << instruction << "\"" << std::endl;
    move(map, direction);
    printMap(map);
  }

  return sumAllBoxes(map);
}

struct Entity {
 public:
  std::tuple<int, int> position;
  bool isRobot = false;
  bool isBox = false;
  std::string name;

  Entity(
      std::tuple<int, int> position, bool isRobot, bool isBox, std::string name
  ) {
    this->position = position;
    this->isRobot = isRobot;
    this->isBox = isBox;
    this->name = name;
  }

  void SetPosition(int row, int col) {
    std::cout << "Moving " << this->name << " from "
              << std::get<0>(this->position) << ", "
              << std::get<1>(this->position) << " to " << row << ", " << col
              << std::endl;
    this->position = std::make_tuple(row, col);
  }

  bool isAbleToMove(
      std::vector<std::vector<std::string>>& map,
      const std::tuple<int, int>& direction, std::vector<Entity>& boxes
  ) {
    auto row = std::get<0>(this->position);
    auto col = std::get<1>(this->position);
    auto rowDirection = std::get<0>(direction);
    auto colDirection = std::get<1>(direction);

    auto nextRow = row + rowDirection;
    auto nextCol = col + colDirection;

    auto nextValue = map[nextRow][nextCol];

    if (this->isRobot) {
      for (auto& box : boxes) {
        auto boxPosition = box.position;
        auto boxRow = std::get<0>(boxPosition);
        auto boxCol = std::get<1>(boxPosition);

        if (nextRow == boxRow && (nextCol == boxCol || nextCol == boxCol + 1)) {
          auto result = box.isAbleToMove(map, direction, boxes);
          if (!result) {
            return false;
          }
        }
      }

      if (nextValue == "#") {
        return false;
      }

      if (nextValue == ".") {
        return true;
      }
    }
    // is box
    else {
      for (auto& box : boxes) {
        auto boxPosition = box.position;
        auto boxRow = std::get<0>(boxPosition);
        auto boxCol = std::get<1>(boxPosition);

        if (nextRow == boxRow && (nextCol == boxCol || nextCol == boxCol + 1) ||
            (nextRow == boxRow && nextCol + 1 == boxCol)) {
          if (this->name == box.name) {
            continue;
          }

          auto result = box.isAbleToMove(map, direction, boxes);
          if (!result) {
            return false;
          }
        }
      }

      if (rowDirection != 0) {
        if (nextValue == "#" || map[nextRow][nextCol + 1] == "#") {
          return false;
        }

        if (nextValue == "." || map[nextRow][nextCol + 1] == ".") {
          return true;
        }
      } else {
        if (nextValue == "#" || map[nextRow][nextCol + 1] == "#") {
          return false;
        }

        if (nextValue == ".") {
          return true;
        }
      }
    }
  }

  bool move(
      std::vector<std::vector<std::string>>& map,
      const std::tuple<int, int>& direction, std::vector<Entity>& boxes
  ) {
    auto isAbleToMove = this->isAbleToMove(map, direction, boxes);
    if (isAbleToMove) {
      auto row = std::get<0>(this->position);
      auto col = std::get<1>(this->position);
      auto rowDirection = std::get<0>(direction);
      auto colDirection = std::get<1>(direction);

      auto nextRow = row + rowDirection;
      auto nextCol = col + colDirection;

      auto nextValue = map[nextRow][nextCol];

      if (this->isRobot) {
        if (nextValue == ".") {
          this->SetPosition(nextRow, nextCol);
        }

        for (auto& box : boxes) {
          auto boxPosition = box.position;
          auto boxRow = std::get<0>(boxPosition);
          auto boxCol = std::get<1>(boxPosition);

          if (nextRow == boxRow &&
              (nextCol == boxCol || nextCol == boxCol + 1)) {
            auto result = box.move(map, direction, boxes);

            if (!result) {
              return false;
            }
          }
        }
      }
      // is box
      else {
        for (auto& box : boxes) {
          auto boxPosition = box.position;
          auto boxRow = std::get<0>(boxPosition);
          auto boxCol = std::get<1>(boxPosition);

          if (this->name == box.name) {
            continue;
          }

          if (nextRow == boxRow &&
                  (nextCol == boxCol || nextCol == boxCol + 1) ||
              (nextRow == boxRow && nextCol + 1 == boxCol)) {
            std::cout << this->name << " caused " << box.name << " to move"
                      << std::endl;
            auto result = box.move(map, direction, boxes);

            if (!result) {
              return false;
            }
          }
        }

        this->SetPosition(nextRow, nextCol);
        return true;
      }
    } else {
      std::cout << "Not able to move : " << isAbleToMove << std::endl;
      return false;
    }
  }
};

int loadMap2(
    const std::vector<std::optional<std::string>>& input,
    std::vector<std::vector<std::string>>& map, Entity& robot,
    std::vector<Entity>& boxes
) {
  for (int i = 0; i < input.size(); i++) {
    if (!input[i].has_value()) {
      return i + 1;
    }
    auto line = input[i].value();

    std::vector<std::string> row = {};
    for (int j = 0; j < line.size(); j++) {
      auto value = line[j];

      if (value == '#') {
        row.push_back("#");
        row.push_back("#");
      }

      if (value == '.') {
        row.push_back(".");
        row.push_back(".");
      }

      if (value == 'O') {
        row.push_back(".");
        row.push_back(".");

        boxes.push_back(Entity(
            std::make_tuple(i, j * 2),
            false,
            true,
            "box " + std::to_string(boxes.size())
        ));
      }

      if (value == '@') {
        row.push_back(".");
        row.push_back(".");

        robot.SetPosition(i, j * 2);
      }
    }
    map.push_back(row);
  }

  return -1;
}

void loadInput2(
    const std::string& filename, std::vector<std::vector<std::string>>& map,
    std::vector<std::string>& instructions, Entity& robot,
    std::vector<Entity>& boxes
) {
  auto input = ReadInput<std::string>(filename);
  auto mapEndIndex = loadMap2(input, map, robot, boxes);
  loadInstructions(mapEndIndex, input, instructions);
}

void printMap2(
    const std::vector<std::vector<std::string>>& map, Entity& robot,
    std::vector<Entity>& boxes
) {
  for (int row = 0; row < map.size(); row++) {
    for (int col = 0; col < map[0].size(); col++) {
      auto robotPosition = robot.position;
      auto robotRow = std::get<0>(robotPosition);
      auto robotCol = std::get<1>(robotPosition);

      auto hasPrinted = false;

      if (row == robotRow && col == robotCol) {
        std::cout << "@";
        hasPrinted = true;
      }

      if (!hasPrinted) {
        for (auto& box : boxes) {
          auto boxPosition = box.position;
          auto boxRow = std::get<0>(boxPosition);
          auto boxCol = std::get<1>(boxPosition);

          if (row == boxRow && col == boxCol) {
            std::cout << "[";
            std::cout << "]";
            col++;
            hasPrinted = true;
            break;
          }
        }
      }

      if (!hasPrinted) {
        std::cout << map[row][col];
      }
    }

    std::cout << std::endl;
  }
}

int sumAllBoxes2(const std::vector<Entity>& boxes) {
  auto sum = 0;

  for (auto box : boxes) {
    auto boxPosition = box.position;
    auto row = std::get<0>(boxPosition);
    auto col = std::get<1>(boxPosition);

    sum += 100 * row + (col);
  }

  return sum;
}

int runPart2(const std::string& filename) {
  std::vector<std::vector<std::string>> map = {};
  std::vector<std::string> instructions = {};
  Entity robot = Entity(std::make_tuple(-1, -1), true, false, "robot");
  std::vector<Entity> boxes = {};

  loadInput2(filename, map, instructions, robot, boxes);

  printMap2(map, robot, boxes);

  int count = 0;
  for (std::string instruction : instructions) {
    count++;
    auto direction = directions[instruction];
    std::cout << std::endl;
    std::cout << "Moving " << count << " \"" << instruction << "\""
              << std::endl;
    robot.move(map, direction, boxes);
    printMap2(map, robot, boxes);
    std::cout << std::endl;
  }

  return sumAllBoxes2(boxes);
}
