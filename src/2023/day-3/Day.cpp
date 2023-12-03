#include <numeric>
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

bool isSymbol(char ch) {
  return !std::isdigit(ch) && ch != '.';
}

bool isAdjacentToSymbol(int row, int col, int numberLength, const std::vector<std::optional<std::string>>& lines) {
  static const int dx[] = {-1, -1, -1, 0, 1, 1, 1, 0, 0};
  static const int dy[] = {-1, 0, 1, 1, 1, 0, -1, -1, 0};

  for (int i = 0; i < numberLength; i++) {
    for (int d = 0; d < 9; d++) {
      int newRow = row + dx[d];
      int newCol = col + i + dy[d];

      if (newRow >= 0 && newRow < lines.size() && newCol >= 0 && newCol < lines[newRow]->length()) {
        if (isSymbol(lines[newRow]->at(newCol))) {
          return true;
        }
      }
    }
  }
  return false;
}

int runPart1(const std::string& filename) {
  std::vector<Part> parts = {};

  auto lines = ReadInput<std::string>(filename);

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

  // Check if each part is a real engine part using directional scanning
  for (auto& part : parts) {
    part.isRealEnginePart = isAdjacentToSymbol(part.row, part.column, part.number.length(), lines);
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
  int row = -1;
  int column = -1;
  int adjacentCount = 0;
  std::vector<std::string> adjacentNumbers = {};
};

int runPart2(const std::string& filename) {
  std::vector<Part> parts = {};
  // key: row-col, val: GearSymbols
  std::unordered_map<std::string, GearSymbols> gearSymbolsMap = {};

  auto lines = ReadInput<std::string>(filename);

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

  // go through all parts
  for (auto& part : parts) {
    int row = -1;
    int col = -1;
    int colLimit = -1;
    bool isRowInBoundaries = false;

    // check top
    row = part.row - 1;
    col = part.column - 1;
    colLimit = col + part.number.length() + 2;

    isRowInBoundaries = row >= 0 && row < lines.size();
    if (isRowInBoundaries) {
      auto line = lines[row];

      if (line.has_value()) {
        // fix col boundaries
        if (col < 0) {
          col = 0;
        }
        if (colLimit > line->length() - 1) {
          colLimit -= 1;
        }

        for (int i = col; i < colLimit; i++) {
          auto letter = line->at(i);

          auto isLetterDigit = std::isdigit(letter);
          auto isPeriod = letter == '.';
          auto isSymbol = !isPeriod && !isLetterDigit;

          if (isSymbol) {
            part.isRealEnginePart = true;

            auto isGearSymbol = letter == '*';
            if (isGearSymbol) {
              auto gearColumn = i;
              auto gearRow = row;

              auto key =
                  std::to_string(gearRow) + "-" + std::to_string(gearColumn);

              auto gearSymbol = gearSymbolsMap.find(key);

              if (gearSymbol != gearSymbolsMap.end()) {
                gearSymbol->second.adjacentCount++;
                gearSymbol->second.adjacentNumbers.push_back(part.number);
              } else {
                gearSymbolsMap[key] = {gearRow, gearColumn, 1, {part.number}};
              }
            }
          }
        }
      }
    }

    // check left
    row = part.row;
    col = part.column - 1;

    // note: always true
    isRowInBoundaries = true;
    if (isRowInBoundaries) {
      auto line = lines[row];

      if (line.has_value()) {
        // only if col in boundaries
        if (col > -1 && col < line->length() - 1) {
          auto letter = line->at(col);

          auto isLetterDigit = std::isdigit(letter);
          auto isPeriod = letter == '.';
          auto isSymbol = !isPeriod && !isLetterDigit;

          if (isSymbol) {
            part.isRealEnginePart = true;

            auto isGearSymbol = letter == '*';
            if (isGearSymbol) {
              auto gearColumn = col;
              auto gearRow = row;

              auto key =
                  std::to_string(gearRow) + "-" + std::to_string(gearColumn);

              auto gearSymbol = gearSymbolsMap.find(key);

              if (gearSymbol != gearSymbolsMap.end()) {
                gearSymbol->second.adjacentCount++;
                gearSymbol->second.adjacentNumbers.push_back(part.number);
              } else {
                gearSymbolsMap[key] = {gearRow, gearColumn, 1, {part.number}};
              }
            }
          }
        }
      }
    }

    // check right
    row = part.row;
    col = part.column + part.number.length();

    // note: always true
    isRowInBoundaries = true;
    if (isRowInBoundaries) {
      auto line = lines[row];

      if (line.has_value()) {
        // only if col in boundaries
        if (col > -1 && col < line->length() - 1) {
          auto letter = line->at(col);

          auto isLetterDigit = std::isdigit(letter);
          auto isPeriod = letter == '.';
          auto isSymbol = !isPeriod && !isLetterDigit;

          if (isSymbol) {
            part.isRealEnginePart = true;

            auto isGearSymbol = letter == '*';
            if (isGearSymbol) {
              auto gearColumn = col;
              auto gearRow = row;

              auto key =
                  std::to_string(gearRow) + "-" + std::to_string(gearColumn);

              auto gearSymbol = gearSymbolsMap.find(key);

              if (gearSymbol != gearSymbolsMap.end()) {
                gearSymbol->second.adjacentCount++;
                gearSymbol->second.adjacentNumbers.push_back(part.number);
              } else {
                gearSymbolsMap[key] = {gearRow, gearColumn, 1, {part.number}};
              }
            }
          }
        }
      }
    }

    // check bottom
    row = part.row + 1;
    col = part.column - 1;
    colLimit = col + part.number.length() + 2;

    isRowInBoundaries = row >= 0 && row < lines.size();
    if (isRowInBoundaries) {
      auto line = lines[row];

      if (line.has_value()) {
        // fix col boundaries
        if (col < 0) {
          col = 0;
        }
        if (colLimit > line->length() - 1) {
          colLimit -= 1;
        }

        for (int i = col; i < colLimit; i++) {
          auto letter = line->at(i);

          auto isLetterDigit = std::isdigit(letter);
          auto isPeriod = letter == '.';
          auto isSymbol = !isPeriod && !isLetterDigit;

          if (isSymbol) {
            part.isRealEnginePart = true;

            auto isGearSymbol = letter == '*';
            if (isGearSymbol) {
              auto gearColumn = i;
              auto gearRow = row;

              auto key =
                  std::to_string(gearRow) + "-" + std::to_string(gearColumn);

              auto gearSymbol = gearSymbolsMap.find(key);

              if (gearSymbol != gearSymbolsMap.end()) {
                gearSymbol->second.adjacentCount++;
                gearSymbol->second.adjacentNumbers.push_back(part.number);
              } else {
                gearSymbolsMap[key] = {gearRow, gearColumn, 1, {part.number}};
              }
            }
          }
        }
      }
    }
  }

  auto sumOfAllGearRatios = 0;

  for (auto [key, gearSymbol] : gearSymbolsMap) {
    if (gearSymbol.adjacentCount == 2) {
      auto firstNumber = gearSymbol.adjacentNumbers[0];
      auto secondNumber = gearSymbol.adjacentNumbers[1];
      auto gearRatio = std::stoi(firstNumber) * std::stoi(secondNumber);

      sumOfAllGearRatios += gearRatio;
    }
  }

  return sumOfAllGearRatios;
}
