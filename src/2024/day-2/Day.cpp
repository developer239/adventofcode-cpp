#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

std::vector<int> isReportSafe(std::vector<int> report) {
  bool isIncreasing;
  std::vector<int> unsafeLevels = {};

  for (int i = 0; i < report.size(); i++) {
    if (i == 0) {
      isIncreasing = report[i] < report[i + 1];
      continue;
    }

    auto prevResult = report[i - 1];
    auto currentResult = report[i];

    auto diff =
        isIncreasing ? currentResult - prevResult : prevResult - currentResult;
    if (diff > 3 || diff < 0 || diff == 0) {
      unsafeLevels.push_back(i-1);
    }
  }

  return unsafeLevels;
}

int runPart1(const std::string& filename) {
  auto result = 0;
  auto lines = ReadInput<std::string>(filename);

  std::vector<std::vector<int>> reports = {};

  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      auto splitResult = splitString(lineValue, ' ');

      std::vector<int> report = {};
      for (auto reportResult : splitResult) {
        report.emplace_back(std::stoi(reportResult));
      }

      reports.emplace_back(report);
    }
  }

  int safeReportsCount = 0;
  for (auto report : reports) {
    auto unsafeLevels = isReportSafe(report);

    if (unsafeLevels.size() == 0) {
      safeReportsCount++;
    }
  }
  result = safeReportsCount;
  return result;
}

int runPart2(const std::string& filename) {
  auto result = 0;
  auto lines = ReadInput<std::string>(filename);

  std::vector<std::vector<int>> reports = {};

  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      auto splitResult = splitString(lineValue, ' ');

      std::vector<int> report = {};
      for (auto reportResult : splitResult) {
        report.emplace_back(std::stoi(reportResult));
      }

      reports.emplace_back(report);
    }
  }

  int safeReportsCount = 0;
  for (auto report : reports) {
    auto unsafeLevels = isReportSafe(report);

    if (unsafeLevels.size() == 0) {
      safeReportsCount++;
      continue;
    }

    bool canBeMadeSafe = false;
    for (int i = 0; i < report.size(); i++) {
      std::vector<int> reportWithoutLevel = report;
      reportWithoutLevel.erase(reportWithoutLevel.begin() + i);

      auto unsafeLevelsAfterRemoval = isReportSafe(reportWithoutLevel);
      if (unsafeLevelsAfterRemoval.size() == 0) {
        canBeMadeSafe = true;
        break;
      }
    }

    if (canBeMadeSafe) {
      safeReportsCount++;
    }
  }

  result = safeReportsCount;
  return result;
}
