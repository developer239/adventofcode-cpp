#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

std::vector<std::pair<int, int>> lineToRanges(std::optional<std::string>& line
) {
  int leftStart, leftEnd, rightStart, rightEnd;
  sscanf(
      line.value().c_str(),
      "%d-%d,%d-%d",
      &leftStart,
      &leftEnd,
      &rightStart,
      &rightEnd
  );

  std::vector<std::pair<int, int>> ranges = {
      {leftStart, leftEnd},
      {rightStart, rightEnd}};

  return ranges;
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int sumFullyOverlappingPairs = 0;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];

    if (line.has_value()) {
      std::vector<std::pair<int, int>> ranges = lineToRanges(line);

      auto firstRange = ranges[0];
      auto secondRange = ranges[1];

      if (firstRange.first >= secondRange.first &&
          firstRange.second <= secondRange.second) {
        sumFullyOverlappingPairs++;
      } else if (secondRange.first >= firstRange.first && secondRange.second <= firstRange.second) {
        sumFullyOverlappingPairs++;
      }
    }
  }

  return sumFullyOverlappingPairs;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int sumPartiallyOverlappingPairs = 0;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];

    if (line.has_value()) {
      std::vector<std::pair<int, int>> ranges = lineToRanges(line);

      auto leftStart = ranges[0].first;
      auto leftEnd = ranges[0].second;
      auto rightStart = ranges[1].first;
      auto rightEnd = ranges[1].second;

      if (leftStart >= rightStart && leftStart <= rightEnd) {
        sumPartiallyOverlappingPairs++;
      } else if (leftEnd >= rightStart && leftEnd <= rightEnd) {
        sumPartiallyOverlappingPairs++;
      } else if (rightStart >= leftStart && rightStart <= leftEnd) {
        sumPartiallyOverlappingPairs++;
      } else if (rightEnd >= leftStart && rightEnd <= leftEnd) {
        sumPartiallyOverlappingPairs++;
      }
    }
  }

  return sumPartiallyOverlappingPairs;
}
