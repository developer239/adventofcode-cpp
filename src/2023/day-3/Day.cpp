#include <functional>
#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

struct Part {
  int row = -1;
  int column = -1;
  std::string number;
  bool isRealEnginePart = false;
};

std::vector<Part> findAllParts(const std::vector<std::optional<std::string>>& lines) {
  std::vector<Part> parts = {};

  for (int row = 0; row < lines.size(); row++) {
    auto line = lines[row];
    if (line.has_value()) {
      std::string partNumber = "";
      int rowStart = 0;
      int columnStart = 0;

      for (int col = 0; col < line->length(); col++) {
        auto letter = line->at(col);

        if (std::isdigit(letter)) {
          if (partNumber.length() == 0) {
            rowStart = row;
            columnStart = col;
          }

          partNumber.push_back(letter);
          continue;
        }

        // add number and reset START
        if (partNumber.length()) {
          parts.push_back({rowStart, columnStart, partNumber});

          partNumber = "";
        }
        // END
      }

      // add number and reset START
      if (partNumber.length()) {
        parts.push_back({rowStart, columnStart, partNumber});

        // technically you don't have to reset you only want to add what is left
        // in the memory
        partNumber = "";
      }
      // END
    }
  }

  return parts;
}

bool isSymbol(char ch) { return !std::isdigit(ch) && ch != '.'; }

struct Direction {
  int dRow;
  int dCol;
};

std::vector<Direction> directions = {
    {-1, -1}, // Top-Left
    {-1,  0}, // Top
    {-1,  1}, // Top-Right
    { 0,  1}, // Right
    { 1,  1}, // Bottom-Right
    { 1,  0}, // Bottom
    { 1, -1}, // Bottom-Left
    { 0, -1}, // Left
};

bool isAdjacentToSymbol(
    int row, int col, int numberLength,
    const std::vector<std::optional<std::string>>& lines,
    std::function<void(int, int, char)> symbolCallback = nullptr
) {
  for (int i = 0; i < numberLength; i++) {
    for (const auto& dir : directions) {
      int newRow = row + dir.dRow;
      int newCol = col + i + dir.dCol;

      if (newRow >= 0 && newRow < lines.size() && newCol >= 0 &&
          newCol < lines[newRow]->length()) {
        char foundSymbol = lines[newRow]->at(newCol);
        if (isSymbol(foundSymbol)) {
          if (symbolCallback) {
            symbolCallback(newRow, newCol, foundSymbol);
          }
          return true;
        }
      }
    }
  }
  return false;
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  auto parts = findAllParts(lines);

  for (auto& part : parts) {
    part.isRealEnginePart =
        isAdjacentToSymbol(part.row, part.column, part.number.length(), lines);
  }

  auto sumOfAllParts = 0;
  for (const auto part : parts) {
    if (part.isRealEnginePart) {
      sumOfAllParts += std::stoi(part.number);
    }
  }

  return sumOfAllParts;
}

struct GearSymbols {
  int adjacentCount = 0;
  std::vector<std::string> adjacentNumbers = {};
};

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  auto parts = findAllParts(lines);

  // key: row-col, val: GearSymbols
  std::unordered_map<std::string, GearSymbols> gearSymbolsMap = {};

  for (auto& part : parts) {
    isAdjacentToSymbol(
        part.row,
        part.column,
        part.number.length(),
        lines,
        [&](int gearRow, int gearCol, char symbol) {
          if (symbol == '*') {
            std::string key =
                std::to_string(gearRow) + "-" + std::to_string(gearCol);
            auto& gearSymbol = gearSymbolsMap[key];

            if (std::find(
                    gearSymbol.adjacentNumbers.begin(),
                    gearSymbol.adjacentNumbers.end(),
                    part.number
                ) == gearSymbol.adjacentNumbers.end()) {
              gearSymbol.adjacentCount++;
              gearSymbol.adjacentNumbers.push_back(part.number);
            }
          }
        }
    );
  }

  // Calculate sum of all gear ratios
  int sumOfAllGearRatios = 0;
  for (auto& [key, gearSymbol] : gearSymbolsMap) {
    if (gearSymbol.adjacentCount == 2) {
      auto gearRatio = std::stoi(gearSymbol.adjacentNumbers[0]) *
                       std::stoi(gearSymbol.adjacentNumbers[1]);
      sumOfAllGearRatios += gearRatio;
    }
  }

  return sumOfAllGearRatios;
}
