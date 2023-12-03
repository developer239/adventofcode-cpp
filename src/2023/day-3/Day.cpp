#include <numeric>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

struct Part {
  int row = -1;
  int column = -1;
  std::string number;
  bool isRealEnginePart = false;
};

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
        if (colLimit > line->length() -1) {
          colLimit -= 1;
        }

        for (int i = col; i < colLimit; i++) {
          auto letter = line->at(i);

          auto isLetterDigit = std::isdigit(letter);
          auto isPeriod = letter == '.';
          auto isSymbol = !isPeriod && !isLetterDigit;

          if (isSymbol) {
            part.isRealEnginePart = true;
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
        if (colLimit > line->length() -1) {
          colLimit -= 1;
        }

        for (int i = col; i < colLimit; i++) {
          auto letter = line->at(i);

          auto isLetterDigit = std::isdigit(letter);
          auto isPeriod = letter == '.';
          auto isSymbol = !isPeriod && !isLetterDigit;

          if (isSymbol) {
            part.isRealEnginePart = true;
          }
        }
      }
    }
  }

  auto sumOfAllParts = 0;

  for (const auto part: parts) {
    if(part.isRealEnginePart) {
      sumOfAllParts += std::stoi(part.number);
    }
  }

  return sumOfAllParts;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  for (auto line : lines) {
    if (line.has_value()) {
    }
  }

  return 0;
}
