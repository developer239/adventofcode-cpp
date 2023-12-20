#include <functional>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

struct Race {
  long long totalRaceTime;
  long long recordDistanceMm;
};

// Time:        60     94     78     82
// Distance:   475   2138   1015   1650
std::vector<Race> ParseInput(const std::string& filename) {
  std::vector<Race> result = {};

  auto lines = ReadInput<std::string>(filename);

  auto raceTime = lines[0];
  auto raceDistance = lines[1];

  auto raceParts = splitString(raceTime.value(), ' ');
  auto distanceParts = splitString(raceDistance.value(), ' ');

  for (long long i = 1; i < raceParts.size(); i++) {
    result.push_back({std::stoi(raceParts[i]), std::stoi(distanceParts[i])});
  }

  return result;
}

long long runPart1(const std::string& filename) {
  auto input = ParseInput(filename);

  std::vector<std::vector<long long>> waysToWin = {};
  for (auto& [totalRaceTime, recordDistanceMm] : input) {
    std::vector<long long> wayToWin = {};

    for (long long holdMs = 1; holdMs < (totalRaceTime); holdMs += 1) {
      auto travelTime = totalRaceTime - holdMs;
      auto travelDistance = travelTime * holdMs;

      if (travelDistance > recordDistanceMm) {
        wayToWin.push_back(holdMs);
      }
    }

    waysToWin.push_back(wayToWin);
  }

  long long totalNumberOfWaysToWin = 0;
  for (auto& wayToWin : waysToWin) {
    if (wayToWin.size()) {
      if (totalNumberOfWaysToWin == 0) {
        totalNumberOfWaysToWin = wayToWin.size();
      } else {
        totalNumberOfWaysToWin *= wayToWin.size();
      }
    }
  }

  return totalNumberOfWaysToWin;
}

long long runPart2(const std::string& filename) {
  auto input = ParseInput(filename);

  Race actualInput = {0, 0};

  for (auto& [totalRaceTime, recordDistanceMm] : input) {
    auto currentTotalRaceTimeString = std::to_string(actualInput.totalRaceTime);
    auto currentRecordDistanceMmString =
        std::to_string(actualInput.recordDistanceMm);

    auto appendTotalRaceTimeString = std::to_string(totalRaceTime);
    auto appendRecordDistanceMmString = std::to_string(recordDistanceMm);

    actualInput.totalRaceTime =
        std::stoll(currentTotalRaceTimeString + appendTotalRaceTimeString);
    actualInput.recordDistanceMm =
        std::stoll(currentRecordDistanceMmString + appendRecordDistanceMmString);
  }

  std::vector<long long> wayToWin = {};
  auto totalRaceTime = actualInput.totalRaceTime;
  auto recordDistanceMm = actualInput.recordDistanceMm;

  for (long long holdMs = 1; holdMs < (totalRaceTime); holdMs += 1) {
    auto travelTime = totalRaceTime - holdMs;
    auto travelDistance = travelTime * holdMs;

    if (travelDistance > recordDistanceMm) {
      wayToWin.push_back(holdMs);
    }
  }

  return wayToWin.size();
}
