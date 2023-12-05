#include <functional>
#include <unordered_map>

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

#include <unordered_map>

class ConversionMap {
 public:
  long long get(int key) const {
    auto it = map.find(key);
    if (it == map.end()) {
      return key;
    }
    return it->second;
  }

  long long& operator[](int key) { return map[key]; }

 private:
  std::unordered_map<long long, long long> map;
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
      int mapValueLineIndex = lineIndex + 1;

      while (lines[mapValueLineIndex].has_value()) {
        auto mapValueLine = lines[mapValueLineIndex].value();
        auto splitMapValueLine = splitString(mapValueLine, ' ');

        long long source = std::stoll(splitMapValueLine[1]);
        long long destination = std::stoll(splitMapValueLine[0]);
        long long range = std::stoll(splitMapValueLine[2]);

        for (int i = 0; i < range; i++) {
          allMaps[mapType][source + i] = destination + i;
        }

        mapValueLineIndex++;
      }

      lineIndex = mapValueLineIndex;
    }
  }

  return {allMaps, seeds};
}

int runPart1(const std::string& filename) {
  auto [allMaps, seeds] = ParseInput(filename);

  // seed-to-soil -> soil-to-fertilizer -> fertilizer-to-water -> water-to-light
  // -> light-to-temperature -> temperature-to-humidity -> humidity-to-location

  std::unordered_map<int, int> seedToLocation = {};

  for (auto seed : seeds) {
    auto soil = allMaps[SEED_TO_SOIL].get(seed);
    auto fertilizer = allMaps[SOIL_TO_FERTILIZER].get(soil);
    auto water = allMaps[FERTILIZER_TO_WATER].get(fertilizer);
    auto light = allMaps[WATER_TO_LIGHT].get(water);
    auto temperature = allMaps[LIGHT_TO_TEMPERATURE].get(light);
    auto humidity = allMaps[TEMPERATURE_TO_HUMIDITY].get(temperature);
    auto location = allMaps[HUMIDITY_TO_LOCATION].get(humidity);

    seedToLocation[seed] = location;
  }

  int lowestLocation = INT_MAX;
  for (auto [seed, location] : seedToLocation) {
    if (location < lowestLocation) {
      lowestLocation = location;
    }
  }

  return lowestLocation;
}

int runPart2(const std::string& filename) { return 0; }
