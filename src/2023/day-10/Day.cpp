#include <map>
#include <numeric>
#include <set>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

enum ExitSide { NORTH = 1, EAST = 2, SOUTH = 3, WEST = 4, NONE = 0 };

// forward declaration for map
struct Tile;
using Map = std::vector<std::vector<Tile>>;

//    |   -   L   J   7   F
// -----------------------------
// |  NS  -    S   S   N   N
// -  -  EW    W   E   E   W
// L  N   E    -   E   NE  N
// J  N   W    W   -   N   NW
// 7  S   W    WS  S   -   W
// F  S   E    S   ES   E  -
const std::map<char, std::map<char, std::set<ExitSide>>> connectivityRules = {
    {'|',
     {{'|', {NORTH, SOUTH}},
      // - none
      {'L', {SOUTH}},
      {'J', {SOUTH}},
      {'7', {NORTH}},
      {'F', {NORTH}}}},
    {'-',
     // | none
     {{'-', {EAST, WEST}},
      {'L', {WEST}},
      {'J', {EAST}},
      {'7', {EAST}},
      {'F', {WEST}}}},
    {'L',
     {
         {'|', {NORTH}},
         {'-', {EAST}},
         // L none
         {'J', {EAST}},
         {'7', {NORTH, EAST}},
         {'F', {NORTH}},
     }},
    {'J',
     {{'|', {NORTH}},
      {'-', {WEST}},
      {'L', {WEST}},
      // J none
      {'7', {NORTH}},
      {'F', {NORTH, WEST}}}},
    {'7',
     {{'|', {SOUTH}},
      {'-', {WEST}},
      {'L', {WEST, SOUTH}},
      {'J', {SOUTH}},
      // 7 none
      {'F', {WEST}}}},
    {'F',
     {
         {'|', {SOUTH}},
         {'-', {EAST}},
         {'L', {SOUTH}},
         {'J', {EAST, SOUTH}},
         {'7', {EAST}},
         // F none
     }},
};

struct Tile {
  char type;
  int row;
  int col;
  int distanceFromStart;

  Tile(char type, int row, int col)
      : type(type), row(row), col(col), distanceFromStart(-1) {}

  [[nodiscard]] bool isConnectedTo(const Tile& other, const Map& map) const {
    if (this->isGround() || other.isGround()) {
      return false;
    }

    int rowDiff = other.row - this->row;
    int colDiff = other.col - this->col;

    ExitSide directionToOther;
    if (rowDiff == -1 && colDiff == 0) {
      directionToOther = NORTH;
    } else if (rowDiff == 1 && colDiff == 0) {
      directionToOther = SOUTH;
    } else if (rowDiff == 0 && colDiff == -1) {
      directionToOther = WEST;
    } else if (rowDiff == 0 && colDiff == 1) {
      directionToOther = EAST;
    } else {
      return false;
    }

    // Handle 'S' tile by trying different pipe types
    if (this->isStart() || other.isStart()) {
      char possibleTypes[] = {'|', '-', 'L', 'J', '7', 'F'};
      for (char type : possibleTypes) {
        Tile tempTile =
            (this->isStart()) ? Tile(type, this->row, this->col) : *this;
        Tile tempOtherTile =
            (other.isStart()) ? Tile(type, other.row, other.col) : other;

        auto findIt = connectivityRules.find(tempTile.type);
        if (findIt != connectivityRules.end()) {
          auto otherIt = findIt->second.find(tempOtherTile.type);
          if (otherIt != findIt->second.end() &&
              otherIt->second.find(directionToOther) != otherIt->second.end()) {
            return true;
          }
        }
      }
      return false;
    }

    auto findIt = connectivityRules.find(this->type);
    if (findIt != connectivityRules.end()) {
      auto otherIt = findIt->second.find(other.type);
      if (otherIt != findIt->second.end()) {
        return otherIt->second.find(directionToOther) != otherIt->second.end();
      }
    }

    return false;
  }

  [[nodiscard]] bool isStart() const { return type == 'S'; }

  [[nodiscard]] bool isGround() const { return type == '.'; }
};

Map ParseInput(const std::string& filename) {
  Map result = {};

  auto lines = ReadInput<std::string>(filename);

  for (int row = 0; row < lines.size(); row++) {
    auto lineValue = lines[row].value();

    std::vector<Tile> rowTiles = {};
    for (int col = 0; col < lineValue.size(); col++) {
      rowTiles.push_back(Tile(lineValue[col], row, col));
    }
    result.push_back(rowTiles);
  }

  return result;
}

Tile findStartTile(const Map& map) {
  for (const auto& row : map) {
    for (const auto& tile : row) {
      if (tile.isStart()) {
        return tile;
      }
    }
  }
}

std::vector<Tile> findConnectedTiles(const Tile& tile, const Map& map) {
  std::vector<Tile> result = {};
  std::vector<std::pair<int, int>> offsets = {{-1, 0}, {1, 0}, {0, -1}, {0, 1}};

  for (const auto& offset : offsets) {
    int newRow = tile.row + offset.first;
    int newCol = tile.col + offset.second;

    if (newRow >= 0 && newRow < map.size() && newCol >= 0 &&
        newCol < map[0].size()) {
      const Tile& otherTile = map[newRow][newCol];
      if (tile.isConnectedTo(otherTile, map)) {
        result.push_back(otherTile);
      }
    }
  }

  return result;
}

int runPart1(const std::string& filename) {
  auto map = ParseInput(filename);
  Tile startTile = findStartTile(map);
  startTile.distanceFromStart = 0;

  std::vector<Tile> loop = {startTile};
  std::set<std::pair<int, int>> visitedTiles;
  visitedTiles.insert({startTile.row, startTile.col});

  std::vector<Tile> toVisit = findConnectedTiles(startTile, map);
  while (!toVisit.empty()) {
    Tile currentTile = toVisit.back();
    toVisit.pop_back();

    if (visitedTiles.find({currentTile.row, currentTile.col}) !=
        visitedTiles.end()) {
      continue;
    }

    currentTile.distanceFromStart = loop.back().distanceFromStart + 1;
    visitedTiles.insert({currentTile.row, currentTile.col});
    loop.push_back(currentTile);

    if (currentTile.isStart() && currentTile.distanceFromStart > 0) {
      break;
    }

    std::vector<Tile> connectedTiles = findConnectedTiles(currentTile, map);
    for (auto& tile : connectedTiles) {
      if (visitedTiles.find({tile.row, tile.col}) == visitedTiles.end()) {
        toVisit.push_back(tile);
      }
    }
  }

  int loopSize = loop.size();
  for (int i = 0; i < loopSize; i++) {
    Tile& tile = loop[i];
    int reverseDistance = loopSize - i;
    tile.distanceFromStart = std::min(tile.distanceFromStart, reverseDistance);
  }

  std::cout << "Loop: " << std::endl;
  for (const auto& tile : loop) {
    std::cout << "Tile: " << tile.type << " at (" << tile.row << ", "
              << tile.col
              << "), Distance from Start: " << tile.distanceFromStart
              << std::endl;
  }

  auto maxDistanceFromStart = std::max_element(
      loop.begin(),
      loop.end(),
      [](const Tile& a, const Tile& b) {
        return a.distanceFromStart < b.distanceFromStart;
      }
  );

  return maxDistanceFromStart->distanceFromStart;
}

int runPart2(const std::string& filename) { return 0; }
