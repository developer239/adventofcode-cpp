#include <utility>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/Tokenize.cpp"

typedef std::vector<int> Point;
typedef std::vector<Point> Directions;

typedef std::vector<std::vector<int>> MatrixInt;
typedef std::vector<std::vector<char>> MatrixChar;

Directions directions = {
    {-1, 0},  // up
    {0, 1},   // right
    {1, 0},   // down
    {0, -1},  // lef
};

Point move(Point current, Point direction) {
  return {current[0] + direction[0], current[1] + direction[1]};
}

struct QueueItem {
  Point point;
  int distance;
  int lastVisited;
};

struct TraversalBFSResult {
  MatrixInt matrix;
  int distance;
};

TraversalBFSResult traversalBFS(MatrixInt matrix, Point start) {
  MatrixInt seen(matrix.size(), std::vector<int>(matrix[0].size(), 0));
  std::vector<QueueItem> queue = {{start, 1, 'a' - 96}};

  int pathLength = -1;
  int count = 1;
  while (!queue.empty()) {
    auto front = queue.front();

    auto lastVisited = front.lastVisited;
    auto distance = front.distance;
    auto row = front.point[0];
    auto col = front.point[1];

    queue.erase(queue.begin());

    if (row < 0 || col < 0 || row >= matrix.size() || col >= matrix[0].size()) {
      continue;
    }

    if (seen[row][col] && seen[row][col] <= distance) {
      continue;
    }

    auto matrixValue = matrix[row][col];
    if (matrixValue - 1 > lastVisited) {
      continue;
    }

    seen[row][col] = distance;
    count++;

    if (matrixValue == 26) {
      if (pathLength == -1 || distance < pathLength) {
        pathLength = distance;
      } else {
        pathLength = std::min(pathLength, distance);
      }
    }

    for (const auto& direction : directions) {
      queue.push_back(
          {move(front.point, direction), distance + 1, matrix[row][col]}
      );
    }
  }

  return {seen, pathLength};
}

MatrixInt parseInput(std::vector<std::optional<std::string>> lines) {
  MatrixInt matrix;

  for (int row = 0; row < lines.size(); row++) {
    matrix.emplace_back();
    for (int col = 0; col < lines[row].value().size(); col++) {
      matrix[row].emplace_back();
      auto value = static_cast<unsigned char>(lines[row].value()[col]);

      int asciiLetterOffset = 96;
      if (value == 'S') {
        matrix[row][col] = 'a' - asciiLetterOffset;
      } else if (value == 'E') {
        matrix[row][col] = 'z' - asciiLetterOffset;
      } else {
        matrix[row][col] = value - asciiLetterOffset;
      }
    }
  }

  return matrix;
}

template <typename T>
void matrixToASCII(T matrix) {
  for (int row = 0; row < matrix.size(); row++) {
    for (int col = 0; col < matrix[row].size(); col++) {
      if constexpr (std::is_same_v<T, MatrixInt>) {
        auto value = std::to_string(matrix[row][col]);

        if (value.length() == 1) {
          value = " " + value;
        }

        std::cout << value << " ";
      } else {
        std::cout << matrix[row][col];
      }
    }
    std::cout << std::endl;
  }
}

Point findStart(std::vector<std::optional<std::string>> lines) {
  for (int row = 0; row < lines.size(); row++) {
    for (int col = 0; col < lines[row].value().size(); col++) {
      if (lines[row].value()[col] == 'S') {
        return {row, col};
      }
    }
  }

  return {0, 0};
}

long runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  bool isDebug = filename.find("example") != std::string::npos;

  auto start = findStart(lines);
  auto input = parseInput(lines);

  auto result = traversalBFS(input, start);

  if (isDebug) {
    matrixToASCII(input);
  }

  std::cout << std::endl;

  if (isDebug) {
    matrixToASCII(result.matrix);
  }

  return result.distance;
}

std::vector<Point> findAllStarts(
    std::vector<std::optional<std::string>> lines, char targetChar
) {
  std::vector<Point> starts;

  for (int row = 0; row < lines.size(); row++) {
    for (int col = 0; col < lines[row].value().size(); col++) {
      if (lines[row].value()[col] == targetChar) {
        starts.push_back({row, col});
      }
    }
  }

  return starts;
}

long runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  bool isDebug = filename.find("example") != std::string::npos;

  auto starts = findAllStarts(lines, 'a');
  auto input = parseInput(lines);

  int shortestDistance = INT_MAX;

  for (auto start : starts) {
    auto result = traversalBFS(input, start);

    if (isDebug) {
      matrixToASCII(input);
      std::cout << std::endl;
      matrixToASCII(result.matrix);
    }

    // 🤯TODO: figure out why does it return result.distance -1
    if (result.distance > 0) {
      shortestDistance = std::min(shortestDistance, result.distance);
    }
  }

  return shortestDistance;
}
