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

struct Move {
  Direction direction;
  int distance;
};

Move entryToMove(const std::string& entry) {
  if (entry.starts_with("U")) {
    return Move{Down, std::stoi(entry.substr(1))};
  }

  if (entry.starts_with("D")) {
    return Move{Up, std::stoi(entry.substr(1))};
  }

  if (entry.starts_with("L")) {
    return Move{Left, std::stoi(entry.substr(1))};
  }

  if (entry.starts_with("R")) {
    return Move{Right, std::stoi(entry.substr(1))};
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

void bridgeToASCII(
    const std::vector<std::vector<int>>& bridge, const Position& head,
    const Position& tail
) {
  auto flippedBridge = bridge;
  std::reverse(flippedBridge.begin(), flippedBridge.end());
  auto flippedHeadPosition =
      Position{static_cast<int>(flippedBridge.size() - head.row - 1), head.col};
  auto flippedTailPosition =
      Position{static_cast<int>(flippedBridge.size() - tail.row - 1), tail.col};

  for (int row = 0; row < flippedBridge.size(); row++) {
    for (int col = 0; col < flippedBridge[row].size(); col++) {
      if (row == flippedHeadPosition.row && col == flippedHeadPosition.col) {
        std::cout << "H";
      } else if (row == flippedTailPosition.row && col == flippedTailPosition.col) {
        std::cout << "T";
      } else if (flippedBridge[row][col] == 1) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
    std::cout << std::endl;
  }
}

void moveTail(
    Position& tail, Position& headStart, std::vector<Position>& route,
    std::vector<std::vector<int>>& bridge
) {
  Position prevPosition = headStart;
  for (auto position : route) {
    if (calculateDistance(position, tail) > 1) {
      tail = prevPosition;
      bridge[tail.row][tail.col] = 1;
    }
    prevPosition = position;
  }
}

void moveHead(Position& head, const Move& move, std::vector<Position>& route) {
  int movedCount = 0;

  while (movedCount < move.distance) {
    switch (move.direction) {
      case Up:
        head.row--;
        break;
      case Down:
        head.row++;
        break;
      case Left:
        head.col--;
        break;
      case Right:
        head.col++;
        break;
    }

    route.push_back(head);
    movedCount++;
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

  auto head = Position{bridgeCenter, bridgeCenter};
  auto tail = Position{bridgeCenter, bridgeCenter};

  // mark starting position
  bridge[tail.row][tail.col] = 1;

  std::vector<Position> headRoute;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];

    if (line.has_value()) {
      if (IS_EXAMPLE) {
        std::cout << "Line " << lineIndex << ": " << line.value() << std::endl;
        bridgeToASCII(bridge, head, tail);
      }
      auto headStart = head;
      auto entry = line.value();
      auto move = entryToMove(entry);

      moveHead(head, move, headRoute);
      moveTail(tail, headStart, headRoute, bridge);
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
