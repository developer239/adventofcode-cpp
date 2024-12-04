#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

bool checkForXMAS(const std::vector<std::string>& grid, int row, int col, int dx, int dy) {
  const std::string target = "XMAS";
  const int height = grid.size();
  const int width = grid[0].size();

  if (row + dx * 3 < 0 || row + dx * 3 >= height ||
      col + dy * 3 < 0 || col + dy * 3 >= width) {
    return false;
  }

  for (int i = 0; i < 4; i++) {
    if (grid[row + dx * i][col + dy * i] != target[i]) {
      return false;
    }
  }

  return true;
}

int countXMASInGrid(const std::vector<std::string>& grid) {
  int count = 0;
  const int height = grid.size();
  const int width = grid[0].size();

  std::vector<std::pair<int, int>> directions = {
      {0, 1},   // right
      {1, 0},   // down
      {1, 1},   // diagonal down-right
      {-1, 1},  // diagonal up-right
      {0, -1},  // left
      {-1, 0},  // up
      {-1, -1}, // diagonal up-left
      {1, -1}   // diagonal down-left
  };

  for (int row = 0; row < height; row++) {
    for (int col = 0; col < width; col++) {
      if (grid[row][col] == 'X') {
        for (const auto& [dx, dy] : directions) {
          if (checkForXMAS(grid, row, col, dx, dy)) {
            count++;
          }
        }
      }
    }
  }

  return count;
}

int runPart1(const std::string& filename) {
  auto input = ReadInput<std::string>(filename);
  std::vector<std::string> grid;

  for (const auto& line : input) {
    if (line.has_value()) {
      grid.push_back(line.value());
    }
  }

  return countXMASInGrid(grid);
}

bool isValidMAS(char first, char last) {
  return (first == 'M' && last == 'S') || // MAS
         (first == 'S' && last == 'M');   // SAM
}

bool checkForMAS(const std::vector<std::string>& grid, int row, int col) {
  if (row <= 0 || row >= grid.size() - 1 ||
      col <= 0 || col >= grid[0].size() - 1) {
    return false;
  }

  if (grid[row][col] != 'A') {
    return false;
  }

  bool diagonal1 = isValidMAS(
      grid[row - 1][col - 1],  // top-left
      grid[row + 1][col + 1]   // bottom-right
  );

  bool diagonal2 = isValidMAS(
      grid[row - 1][col + 1],  // top-right
      grid[row + 1][col - 1]   // bottom-left
  );

  return diagonal1 && diagonal2;
}

int countMASInGrid(const std::vector<std::string>& grid) {
  int count = 0;
  const int height = grid.size();
  const int width = grid[0].size();

  for (int row = 1; row < height - 1; row++) {
    for (int col = 1; col < width - 1; col++) {
      if (grid[row][col] == 'A' && checkForMAS(grid, row, col)) {
        count++;
      }
    }
  }

  return count;
}

int runPart2(const std::string& filename) {
  auto input = ReadInput<std::string>(filename);
  std::vector<std::string> grid;

  for (const auto& line : input) {
    if (line.has_value()) {
      grid.push_back(line.value());
    }
  }

  return countMASInGrid(grid);
}
