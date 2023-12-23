#include <numeric>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

struct Galaxy {
  int id;
  int row;
  int col;
};

struct StarMap {
  std::vector<std::vector<char>> map;
  std::vector<Galaxy> galaxies;
  std::vector<std::pair<Galaxy, Galaxy>> pairs;

  StarMap() = default;

  void ExpandMap() {
    for (int row = 0; row < map.size(); row++) {
      if (IsLineEmpty(row)) {
        map.insert(map.begin() + row + 1, map[row]);
        row++;
      }
    }

    for (int col = 0; col < map[0].size(); col++) {
      if (IsColumnEmpty(col)) {
        for (int row = 0; row < map.size(); row++) {
          map[row].insert(map[row].begin() + col + 1, map[row][col]);
        }
        col++;
      }
    }
  }

  bool IsLineEmpty(int row) const {
    for (int col = 0; col < map[row].size(); col++) {
      if (map[row][col] != '.') {
        return false;
      }
    }

    return true;
  }

  bool IsColumnEmpty(int col) const {
    for (int row = 0; row < map.size(); row++) {
      if (map[row][col] != '.') {
        return false;
      }
    }

    return true;
  }

  void FindGalaxies() {
    for (int row = 0; row < map.size(); row++) {
      for (int col = 0; col < map[row].size(); col++) {
        if (map[row][col] == '#') {
          galaxies.push_back(
              Galaxy{static_cast<int>(galaxies.size() + 1), row, col}
          );
        }
      }
    }
  }

  void FindAllPairs() {
    for (int i = 0; i < galaxies.size(); i++) {
      for (int j = i + 1; j < galaxies.size(); j++) {
        pairs.push_back(std::make_pair(galaxies[i], galaxies[j]));
      }
    }
  }

  int FindShortestPath(Galaxy firstGalaxy, Galaxy secondGalaxy) {
    int rowDistance = std::abs(firstGalaxy.row - secondGalaxy.row);
    int colDistance = std::abs(firstGalaxy.col - secondGalaxy.col);

    int pathLength = 0;
    while(rowDistance > 0 || colDistance > 0) {
      if(rowDistance > colDistance) {
        rowDistance--;
        pathLength++;
      } else {
        colDistance--;
        pathLength++;
      }
    }

    return pathLength;
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
      std::cout << "Galaxy " << galaxy.id << " at (" << galaxy.row << ", "
                << galaxy.col << ")" << std::endl;
    }
  }
};

StarMap ParseInput(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  StarMap map;

  for (int row = 0; row < lines.size(); row++) {
    if (!lines[row].has_value()) {
      continue;
    }

    auto lineValue = lines[row].value();

    std::vector<char> rowTiles = {};
    for (int col = 0; col < lineValue.size(); col++) {
      rowTiles.push_back(lineValue[col]);
    }

    map.map.push_back(rowTiles);
  }

  return map;
}

int runPart1(const std::string& filename) {
  auto map = ParseInput(filename);
  map.ExpandMap();
  map.LogMap();
  map.FindGalaxies();
  map.LogGalaxies();
  map.FindAllPairs();

//  auto shortestPathOneSeven = map.FindShortestPath(map.galaxies[0], map.galaxies[6]);
//  auto shortestPathThreeSix = map.FindShortestPath(map.galaxies[2], map.galaxies[5]);
//  auto shortestPathEightNine = map.FindShortestPath(map.galaxies[7], map.galaxies[8]);
//  auto shortestPathFiveNine = map.FindShortestPath(map.galaxies[4], map.galaxies[8]);

  int distancesSum = 0;
  for(auto& pair : map.pairs) {
    distancesSum += map.FindShortestPath(pair.first, pair.second);
  }

  return distancesSum;
}

int runPart2(const std::string& filename) {
  auto result = 0;

  return result;
}
