#include <numeric>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

struct Galaxy {
  long long id;
  long long row;
  long long col;

  long long offsetRow;
  long long offsetCol;
};

struct StarMap {
  std::vector<std::vector<char>> map;
  std::vector<Galaxy> galaxies;
  std::vector<std::pair<Galaxy, Galaxy>> pairs;

  StarMap() = default;

  void ExpandMap() {
    for (long long row = 0; row < map.size(); row++) {
      if (IsLineEmpty(row)) {
        map.insert(map.begin() + row + 1, map[row]);
        row++;
      }
    }

    for (long long col = 0; col < map[0].size(); col++) {
      if (IsColumnEmpty(col)) {
        for (long long row = 0; row < map.size(); row++) {
          map[row].insert(map[row].begin() + col + 1, map[row][col]);
        }
        col++;
      }
    }
  }

  void ExpandMapPart2() {
    long long offset = 1000000-1;

    long long cumulativeRowOffset = 0;
    long long cumulativeColOffset = 0;

    for (long long row = 0; row < map.size(); row++) {
      if (IsLineEmpty(row)) {
        cumulativeRowOffset += offset;
      } else {
        OffsetAllGalaxiesAtRow(row, cumulativeRowOffset);
      }
    }

    for (long long col = 0; col < map[0].size(); col++) {
      if (IsColumnEmpty(col)) {
        cumulativeColOffset += offset;
      } else {
        OffsetAllGalaxiesAtCol(col, cumulativeColOffset);
      }
    }
  }

  void OffsetAllGalaxiesAtRow(long long row, long long offset) {
    for (auto& galaxy : galaxies) {
      if (galaxy.row == row) {
        galaxy.offsetRow = galaxy.row + offset;
      }
    }
  }

  void OffsetAllGalaxiesAtCol(long long col, long long offset) {
    for (auto& galaxy : galaxies) {
      if (galaxy.col == col) {
        galaxy.offsetCol = galaxy.col + offset;
      }
    }
  }

  bool IsLineEmpty(long long row) const {
    for (long long col = 0; col < map[row].size(); col++) {
      if (map[row][col] != '.') {
        return false;
      }
    }

    return true;
  }

  bool IsColumnEmpty(long long col) const {
    for (long long row = 0; row < map.size(); row++) {
      if (map[row][col] != '.') {
        return false;
      }
    }

    return true;
  }

  void FindGalaxies() {
    for (long long row = 0; row < map.size(); row++) {
      for (long long col = 0; col < map[row].size(); col++) {
        if (map[row][col] == '#') {
          galaxies.push_back(
              Galaxy{static_cast<long long>(galaxies.size() + 1), row, col}
          );
        }
      }
    }
  }

  void FindAllPairs() {
    for (long long i = 0; i < galaxies.size(); i++) {
      for (long long j = i + 1; j < galaxies.size(); j++) {
        pairs.push_back(std::make_pair(galaxies[i], galaxies[j]));
      }
    }
  }

  long long FindShortestPath(Galaxy firstGalaxy, Galaxy secondGalaxy) {
    long long rowDistance = std::abs(firstGalaxy.row - secondGalaxy.row);
    long long colDistance = std::abs(firstGalaxy.col - secondGalaxy.col);

    return rowDistance + colDistance;
  }

  long long FindShortestPathPart2(Galaxy firstGalaxy, Galaxy secondGalaxy) {
    long long rowDistance = std::abs(firstGalaxy.offsetRow - secondGalaxy.offsetRow);
    long long colDistance = std::abs(firstGalaxy.offsetCol - secondGalaxy.offsetCol);

    return rowDistance + colDistance;
  }

  void LogMap() const {
    for (auto& row : map) {
      for (auto& col : row) {
        std::cout << col;
      }
      std::cout << std::endl;
    }
  }

  void LogGalaxies() const {
    for (auto& galaxy : galaxies) {
      std::cout << "Galaxy " << galaxy.id << " at (" << galaxy.offsetRow << ", " << galaxy.offsetCol << ")" << std::endl;
    }
  }
};

StarMap ParseInput(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  StarMap map;

  for (long long row = 0; row < lines.size(); row++) {
    if (!lines[row].has_value()) {
      continue;
    }

    auto lineValue = lines[row].value();

    std::vector<char> rowTiles = {};
    for (long long col = 0; col < lineValue.size(); col++) {
      rowTiles.push_back(lineValue[col]);
    }

    map.map.push_back(rowTiles);
  }

  return map;
}

long long runPart1(const std::string& filename) {
  auto map = ParseInput(filename);
  map.ExpandMap();
  map.LogMap();
  map.FindGalaxies();
  map.LogGalaxies();
  map.FindAllPairs();

  //  auto shortestPathOneSeven = map.FindShortestPath(map.galaxies[0],
  //  map.galaxies[6]); auto shortestPathThreeSix =
  //  map.FindShortestPath(map.galaxies[2], map.galaxies[5]); auto
  //  shortestPathEightNine = map.FindShortestPath(map.galaxies[7],
  //  map.galaxies[8]); auto shortestPathFiveNine =
  //  map.FindShortestPath(map.galaxies[4], map.galaxies[8]);

  long long distancesSum = 0;
  for (auto& pair : map.pairs) {
    distancesSum += map.FindShortestPath(pair.first, pair.second);
  }

  return distancesSum;
}

long long runPart2(const std::string& filename) {
  auto map = ParseInput(filename);
  map.FindGalaxies();
  map.ExpandMapPart2();
  map.FindAllPairs();
  map.LogGalaxies();

  //  auto shortestPathOneSeven = map.FindShortestPath(map.galaxies[0],
  //  map.galaxies[6]); auto shortestPathThreeSix =
  //  map.FindShortestPath(map.galaxies[2], map.galaxies[5]); auto
  //  shortestPathEightNine = map.FindShortestPath(map.galaxies[7],
  //  map.galaxies[8]); auto shortestPathFiveNine =
  //  map.FindShortestPath(map.galaxies[4], map.galaxies[8]);

  long long distancesSum = 0;
  for (auto& pair : map.pairs) {
    distancesSum += map.FindShortestPathPart2(pair.first, pair.second);
  }

  return distancesSum;
}
