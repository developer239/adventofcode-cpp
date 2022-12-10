#include <utility>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

//== Initial State ==
//
// ......
// ......
// ......
// ......
// H.....  (H covers T, s)

//== Initial State ==
//
// H..... (H covers T, s)
// ......
// ......
// ......
// ......

struct Position {
  int row;
  int col;
};

enum Direction {
  Up,
  Down,
  Left,
  Right,
};

struct Movement {
  Direction direction;
  int distance;
};

Movement entryToMovement(const std::string& entry) {
  if (entry.starts_with("U")) {
    return Movement{Down, std::stoi(entry.substr(1))};
  }

  if (entry.starts_with("D")) {
    return Movement{Up, std::stoi(entry.substr(1))};
  }

  if (entry.starts_with("L")) {
    return Movement{Left, std::stoi(entry.substr(1))};
  }

  if (entry.starts_with("R")) {
    return Movement{Right, std::stoi(entry.substr(1))};
  }

  throw std::runtime_error("Invalid move entry");
}

int calculateDistance(const Position& head, const Position& tail) {
  int rowDistance = head.row - tail.row;
  int colDistance = head.col - tail.col;

  if (std::abs(rowDistance) == std::abs(colDistance)) {
    return std::abs(rowDistance);
  }

  if (std::abs(rowDistance) > std::abs(colDistance)) {
    return std::abs(rowDistance);
  } else {
    return std::abs(colDistance);
  }
}

class Node {
 public:
  std::shared_ptr<Node> prev;
  std::shared_ptr<Node> next;
  Position position;
  char label;

  Node(Position position, char label) {
    this->position = position;
    this->label = label;
  }

  void move(const Movement& movement, std::vector<std::vector<int>>& bridge) {
    int movedCount = 0;

    while (movedCount < movement.distance) {
      switch (movement.direction) {
        case Up:
          this->position.row--;
          break;
        case Down:
          this->position.row++;
          break;
        case Left:
          this->position.col--;
          break;
        case Right:
          this->position.col++;
          break;
      }

      moveChildren(movement, bridge);
      movedCount++;
    }
  }

  void moveChildren(
      const Movement& movement, std::vector<std::vector<int>>& bridge
  ) {
    auto parentNode = this;
    auto childNode = this->next;

    while (childNode != nullptr) {
      if (calculateDistance(parentNode->position, childNode->position) > 1) {
        // if was diagonal move
        if (parentNode->position.row != childNode->position.row &&
            parentNode->position.col != childNode->position.col) {
          // if was diagonal move up
          if (parentNode->position.row > childNode->position.row) {
            childNode->position.row++;
          } else {
            childNode->position.row--;
          }

          // if was diagonal move left
          if (parentNode->position.col > childNode->position.col) {
            childNode->position.col++;
          } else {
            childNode->position.col--;
          }
        } else {
          // if was vertical move
          if (parentNode->position.row != childNode->position.row) {
            // if was vertical move up
            if (parentNode->position.row > childNode->position.row) {
              childNode->position.row++;
            } else {
              childNode->position.row--;
            }
          } else {
            // if was horizontal move left
            if (parentNode->position.col > childNode->position.col) {
              childNode->position.col++;
            } else {
              childNode->position.col--;
            }
          }
        }

        if (childNode->isTail()) {
          bridge[childNode->position.row][childNode->position.col] = 1;
        }
      }

      parentNode = childNode.get();
      childNode = childNode->next;
    }
  }

  void append(const std::shared_ptr<Node>& node) {
    this->next = node;
    node->prev = std::make_shared<Node>(*this);
  }

  bool isHead() { return prev == nullptr; }

  bool isTail() { return next == nullptr; }
};

void bridgeToASCII(
    const std::vector<std::vector<int>>& bridge,
    const std::shared_ptr<Node>& head
) {
  auto flippedBridge = bridge;
  std::reverse(flippedBridge.begin(), flippedBridge.end());

  for (int row = 0; row < flippedBridge.size(); row++) {
    for (int col = 0; col < flippedBridge[row].size(); col++) {
      std::shared_ptr<Node> headTemp = head;
      bool shouldSkip = false;

      while (headTemp != nullptr) {
        auto flippedHeadTempPosition = Position{
            static_cast<int>(flippedBridge.size() - headTemp->position.row - 1),
            headTemp->position.col};
        if (flippedHeadTempPosition.row == row &&
            flippedHeadTempPosition.col == col) {
          std::cout << headTemp->label;
          shouldSkip = true;
          break;
        }

        headTemp = headTemp->next;
      }

      if (shouldSkip) {
        continue;
      }

      if (flippedBridge[row][col] == 1) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  bool IS_EXAMPLE = filename.find("example") != std::string::npos;

  int bridgeSize = IS_EXAMPLE ? 8 : 1000;
  int bridgeCenter = IS_EXAMPLE ? 0 : bridgeSize / 2;

  std::vector<std::vector<int>> bridge(
      bridgeSize,
      std::vector<int>(bridgeSize, 0)
  );

  auto head = std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, 'H');
  head->append(std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, 'T')
  );

  // mark starting position
  bridge[head->position.row][head->position.col] = 1;

  std::vector<Position> headRoute;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];

    if (line.has_value()) {
      if (IS_EXAMPLE) {
        std::cout << "Line " << lineIndex << ": " << line.value() << std::endl;
        bridgeToASCII(bridge, head);
      }
      auto entry = line.value();
      auto movement = entryToMovement(entry);

      head->move(movement, bridge);

      headRoute.clear();
    }
  }

  int visitedCount = 0;
  for (int row = 0; row < bridge.size(); row++) {
    for (int col = 0; col < bridge[row].size(); col++) {
      if (bridge[row][col] == 1) {
        visitedCount++;
      }
    }
  }

  return visitedCount;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  bool IS_EXAMPLE = filename.find("example") != std::string::npos;

  int bridgeSize = IS_EXAMPLE ? 200 : 1000;
  int bridgeCenter = IS_EXAMPLE ? 100 : bridgeSize / 2;

  std::vector<std::vector<int>> bridge(
      bridgeSize,
      std::vector<int>(bridgeSize, 0)
  );

  auto head = std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, 'H');
  head->append(std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '1')
  );
  head->next->append(
      std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '2')
  );
  head->next->next->append(
      std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '3')
  );
  head->next->next->next->append(
      std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '4')
  );
  head->next->next->next->next->append(
      std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '5')
  );
  head->next->next->next->next->next->append(
      std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '6')
  );
  head->next->next->next->next->next->next->append(
      std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '7')
  );
  head->next->next->next->next->next->next->next->append(
      std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '8')
  );
  head->next->next->next->next->next->next->next->next->append(
      std::make_shared<Node>(Position{bridgeCenter, bridgeCenter}, '9')
  );

  // mark starting position
  bridge[head->position.row][head->position.col] = 1;

  std::vector<Position> headRoute;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];

    if (line.has_value()) {
      if (IS_EXAMPLE) {
        std::cout << "Line " << lineIndex << ": " << line.value() << std::endl;
      }
      auto entry = line.value();
      auto movement = entryToMovement(entry);

      head->move(movement, bridge);

      headRoute.clear();
    }
  }

  int visitedCount = 0;
  for (int row = 0; row < bridge.size(); row++) {
    for (int col = 0; col < bridge[row].size(); col++) {
      if (bridge[row][col] == 1) {
        visitedCount++;
      }
    }
  }

  return visitedCount;
}
