#include <utility>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

void moveUp(int& tempRow, int& tempCol) { tempRow--; }
void moveDown(int& tempRow, int& tempCol) { tempRow++; }
void moveLeft(int& tempRow, int& tempCol) { tempCol--; }
void moveRight(int& tempRow, int& tempCol) { tempCol++; }

bool checkTop(
    int& tempRow, int& tempCol, const std::vector<std::vector<int>>& grid,
    const int currenTreeSize
) {
  while (tempRow > 0) {
    moveUp(tempRow, tempCol);

    int neighbourTreeSize = grid[tempRow][tempCol];
    if (neighbourTreeSize >= currenTreeSize) {
      return false;
    }
  }

  return true;
}

bool checkLeft(
    int& tempRow, int& tempCol, const std::vector<std::vector<int>>& grid,
    const int currenTreeSize
) {
  while (tempCol > 0) {
    moveLeft(tempRow, tempCol);

    int neighbourTreeSize = grid[tempRow][tempCol];
    if (neighbourTreeSize >= currenTreeSize) {
      return false;
    }
  }

  return true;
}

bool checkRight(
    int& tempRow, int& tempCol, const std::vector<std::vector<int>>& grid,
    const int currenTreeSize
) {
  while (tempCol < grid[tempRow].size() - 1) {
    moveRight(tempRow, tempCol);

    int neighbourTreeSize = grid[tempRow][tempCol];
    if (neighbourTreeSize >= currenTreeSize) {
      return false;
    }
  }

  return true;
}

bool checkDown(
    int& tempRow, int& tempCol, const std::vector<std::vector<int>>& grid,
    const int currenTreeSize
) {
  while (tempRow < grid.size() - 1) {
    moveDown(tempRow, tempCol);

    int neighbourTreeSize = grid[tempRow][tempCol];
    if (neighbourTreeSize >= currenTreeSize) {
      return false;
    }
  }

  return true;
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  std::vector<std::vector<int>> trees;

  for (auto& line : lines) {
    std::vector<int> tree;
    if (line.has_value()) {
      for (auto& c : line.value()) {
        int cInt = c - '0';
        tree.push_back(cInt);
      }
      trees.push_back(tree);
    }
  }

  int visibleTreesCount = 0;
  for (int row = 0; row < trees.size(); row++) {
    for (int col = 0; col < trees[row].size(); col++) {
      int currenTreeSize = trees[row][col];
      bool isVisible = false;

      int rowTemp = row;
      int colTemp = col;
      isVisible = checkTop(rowTemp, colTemp, trees, currenTreeSize);

      if (isVisible) {
        visibleTreesCount++;
        continue;
      }

      rowTemp = row;
      colTemp = col;
      isVisible = checkLeft(rowTemp, colTemp, trees, currenTreeSize);

      if (isVisible) {
        visibleTreesCount++;
        continue;
      }

      rowTemp = row;
      colTemp = col;
      isVisible = checkRight(rowTemp, colTemp, trees, currenTreeSize);

      if (isVisible) {
        visibleTreesCount++;
        continue;
      }

      rowTemp = row;
      colTemp = col;
      isVisible = checkDown(rowTemp, colTemp, trees, currenTreeSize);

      if (isVisible) {
        visibleTreesCount++;
        continue;
      }
    }
  }

  return visibleTreesCount;
}
