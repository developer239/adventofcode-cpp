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

  return std::abs(rowDistance) + std::abs(colDistance);
}

void bridgeToASCII(
    const std::vector<std::vector<int>>& bridge, const Position& head,
    const Position& tail
) {
  // flip bridge vertically
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
    Position& head, Position& prevHead, Position& tail,
    std::vector<std::vector<int>>& bridge
) {
  // is tail around head?
  if (calculateDistance(head, tail) > 1) {
    tail = prevHead;
    bridge[tail.row][tail.col] = 1;
  }
}

void moveHead(
    Position& head, Position& tail, const Move& move,
    std::vector<std::vector<int>>& bridge
) {
  int movedCount = 0;

  while (movedCount < move.distance) {
    auto prevHead = head;
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

    moveTail(head, prevHead, tail, bridge);
    movedCount++;
  }
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  std::vector<std::vector<int>> bridge(1000, std::vector<int>(1000, 0));

  auto head = Position{500, 500};
  auto tail = Position{500, 500};

  // mark starting position
  bridge[tail.row][tail.col] = 1;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];

    if (line.has_value()) {
//      bridgeToASCII(bridge, head, tail);
      auto entry = line.value();
      auto move = entryToMove(entry);

      moveHead(head, tail, move, bridge);
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
