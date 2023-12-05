#include <algorithm>
#include <functional>
#include <limits>
#include <string>
#include <unordered_map>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/SplitString.cpp"

enum MapType {
  SEED_TO_SOIL = 1,
  SOIL_TO_FERTILIZER = 2,
  FERTILIZER_TO_WATER = 3,
  WATER_TO_LIGHT = 4,
  LIGHT_TO_TEMPERATURE = 5,
  TEMPERATURE_TO_HUMIDITY = 6,
  HUMIDITY_TO_LOCATION = 7
};

class ConversionMap {
 public:
  void addRange(
      long long sourceStart, long long destinationStart, long long length
  ) {
    ranges.push_back({sourceStart, destinationStart, length});
  }

  long long operator[](long long key) const {
    for (const auto& range : ranges) {
      if (key >= range.sourceStart && key < range.sourceStart + range.length) {
        return range.destinationStart + key - range.sourceStart;
      }
    }
    return key;
  }

 private:
  struct Range {
    long long sourceStart;
    long long destinationStart;
    long long length;
  };
  std::vector<Range> ranges;
};

using AllMaps = std::unordered_map<MapType, ConversionMap>;

struct PuzzleInput {
  AllMaps allMaps;
  std::vector<long long> seeds;
};

// seeds: 79 14 55 13
//
// seed-to-soil map:
// 50 98 2
// 52 50 48
//
// soil-to-fertilizer map:
// 0 15 37
// 37 52 2
// 39 0 15
//
// fertilizer-to-water map:
// 49 53 8
// 0 11 42
// 42 0 7
// 57 7 4
//
// water-to-light map:
// 88 18 7
// 18 25 70
//
// light-to-temperature map:
// 45 77 23
// 81 45 19
// 68 64 13
//
// temperature-to-humidity map:
// 0 69 1
// 1 0 69
//
// humidity-to-location map:
// 60 56 37
// 56 93 4
PuzzleInput ParseInput(const std::string& filename) {
  using LineToMapType = std::unordered_map<std::string, MapType>;
  LineToMapType lineToMapType = {
      {"seed-to-soil map:", SEED_TO_SOIL},
      {"soil-to-fertilizer map:", SOIL_TO_FERTILIZER},
      {"fertilizer-to-water map:", FERTILIZER_TO_WATER},
      {"water-to-light map:", WATER_TO_LIGHT},
      {"light-to-temperature map:", LIGHT_TO_TEMPERATURE},
      {"temperature-to-humidity map:", TEMPERATURE_TO_HUMIDITY},
      {"humidity-to-location map:", HUMIDITY_TO_LOCATION},
  };

  auto lines = ReadInput<std::string>(filename);

  AllMaps allMaps = {};

  auto seedLine = lines[0].value();
  auto splitStringResult = splitString(splitString(seedLine, ':')[1], ' ');

  std::vector<long long> seeds;
  std::transform(
      splitStringResult.begin(),
      splitStringResult.end(),
      std::back_inserter(seeds),
      [](const std::string& s) { return std::stoll(s); }
  );

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    if (!lines[lineIndex].has_value()) {
      continue;
    }

    auto line = lines[lineIndex].value();
    auto mapType = lineToMapType[line];

    if (mapType) {
      auto mapValueLineIndex = lineIndex + 1;

      while (mapValueLineIndex < lines.size() &&
             lines[mapValueLineIndex].has_value()) {
        auto mapValueLine = lines[mapValueLineIndex].value();
        auto splitMapValueLine = splitString(mapValueLine, ' ');

        long long sourceStart = std::stoll(splitMapValueLine[1]);
        long long destinationStart = std::stoll(splitMapValueLine[0]);
        long long length = std::stoll(splitMapValueLine[2]);

        allMaps[mapType].addRange(sourceStart, destinationStart, length);

        mapValueLineIndex++;
      }

      lineIndex = mapValueLineIndex;
    }
  }

  return {allMaps, seeds};
}

std::string runPart1(const std::string& filename) {
  auto [allMaps, seeds] = ParseInput(filename);

  std::unordered_map<long long, long long> seedToLocation = {};

  for (auto seed : seeds) {
    auto soil = allMaps[SEED_TO_SOIL][seed];
    auto fertilizer = allMaps[SOIL_TO_FERTILIZER][soil];
    auto water = allMaps[FERTILIZER_TO_WATER][fertilizer];
    auto light = allMaps[WATER_TO_LIGHT][water];
    auto temperature = allMaps[LIGHT_TO_TEMPERATURE][light];
    auto humidity = allMaps[TEMPERATURE_TO_HUMIDITY][temperature];
    auto location = allMaps[HUMIDITY_TO_LOCATION][humidity];

    seedToLocation[seed] = location;
  }

  long long lowestLocation = std::numeric_limits<long long>::max();
  for (auto [seed, location] : seedToLocation) {
    if (location < lowestLocation) {
      lowestLocation = location;
    }
  }

  return std::to_string(lowestLocation);
}

int runPart2(const std::string& filename) { return 0; }
