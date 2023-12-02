#include <algorithm>
#include <cctype>
#include <locale>
#include <numeric>
#include <unordered_map>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

static inline void ltrim(std::string& s) {
  s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
            return !std::isspace(ch);
          }));
}

static inline void rtrim(std::string& s) {
  s.erase(
      std::find_if(
          s.rbegin(),
          s.rend(),
          [](unsigned char ch) { return !std::isspace(ch); }
      ).base(),
      s.end()
  );
}

std::vector<std::string> splitString(std::string str, char separator) {
  std::vector<std::string> strings;
  int startIndex = 0, endIndex = 0;
  for (int i = 0; i <= str.size(); i++) {
    if (str[i] == separator || i == str.size()) {
      endIndex = i;
      std::string temp;
      temp.append(str, startIndex, endIndex - startIndex);
      strings.push_back(temp);
      startIndex = endIndex + 1;
    }
  }

  return strings;
}

std::unordered_map<std::string, int> defaultGameConfiguration = {
    {"red", 12}, {"green", 13}, {"blue", 14}};

std::unordered_map<std::string, int> emptyGameConfiguration = {
    {"red", 0}, {"green", 0}, {"blue", 0}};

int runPart1(const std::string& filename) {
  std::vector<int> invalidGameIds = {};
  std::vector<int> validGameIds = {};
  auto lines = ReadInput<std::string>(filename);

  for (auto line : lines) {
    if (line.has_value()) {
      auto lineValue = line.value();

      auto gameData = splitString(lineValue, ':');

      auto gameIdString = gameData[0];
      auto allGameSetsString = gameData[1];

      int gameId;
      sscanf(gameIdString.c_str(), "Game %d", &gameId);

      auto gameSets = splitString(allGameSetsString, ';');
      for (const auto& gameSetAsString : gameSets) {
        auto currentGameConfiguration = emptyGameConfiguration;
        auto gameSetCubesSets = splitString(gameSetAsString, ',');

        for (auto& cubeSet : gameSetCubesSets) {
          ltrim(cubeSet);
          rtrim(cubeSet);

          auto splitSet = splitString(cubeSet, ' ');

          currentGameConfiguration[splitSet[1]] = std::stoi(splitSet[0]);
        }

        for (auto& defaultConfigurationItem : defaultGameConfiguration) {
          auto defaultConfigurationLimit = defaultConfigurationItem.second;
          auto currentConfigurationValue =
              currentGameConfiguration[defaultConfigurationItem.first];

          if (currentConfigurationValue > defaultConfigurationLimit) {
            invalidGameIds.push_back(gameId);
            break;
          }
        }
      }

      int count =
          std::count(invalidGameIds.begin(), invalidGameIds.end(), gameId);
      if (count == 0) {
        validGameIds.push_back(gameId);
      }
    }
  }

  auto idsSum = std::accumulate(validGameIds.begin(), validGameIds.end(), 0);

  return idsSum;
}

int runPart2(const std::string& filename) {
  auto totalPowerSum = 0;
  std::vector<int> invalidGameIds = {};
  std::vector<int> validGameIds = {};
  auto lines = ReadInput<std::string>(filename);

  for (auto line : lines) {
    // loop lines: Game 1: 3 blue, 4 red; 1 red, 2 green, 6 blue; 2 green
    if (line.has_value()) {
      auto lineValue = line.value();

      auto gameData = splitString(lineValue, ':');

      auto gameIdString = gameData[0];
      auto allGameSetsString = gameData[1];

      int gameId;
      sscanf(gameIdString.c_str(), "Game %d", &gameId);

      auto minimalPossibleCurrentGameConfiguration = emptyGameConfiguration;

      auto gameSets = splitString(allGameSetsString, ';');
      // loop game sets
      // {" 3 blue, 4 red"
      // " 1 red, 2 green, 6 blue"
      // " 2 green"}
      for (const auto& gameSetAsString : gameSets) {
        auto currentGameConfiguration = emptyGameConfiguration;

        // {" 3 blue"
        // " 4 red"}
        auto gameSetCubesSets = splitString(gameSetAsString, ',');

        for (auto& cubeSet : gameSetCubesSets) {
          // "3 blue"
          ltrim(cubeSet);
          rtrim(cubeSet);

          auto splitSet = splitString(cubeSet, ' ');

          // "blue"
          auto key = splitSet[1];
          // 3
          auto currentValue = std::stoi(splitSet[0]);

          currentGameConfiguration[key] = currentValue;
        }

        for (auto& defaultConfigurationItem : defaultGameConfiguration) {
          auto defaultConfigurationLimit = defaultConfigurationItem.second;
          auto currentConfigurationValue =
              currentGameConfiguration[defaultConfigurationItem.first];

          if (currentConfigurationValue > defaultConfigurationLimit) {
            invalidGameIds.push_back(gameId);
            break;
          }
        }

        // actual part 2
        for(auto& currentConfigurationItem: currentGameConfiguration) {
          auto currentItemCurrentValue = currentConfigurationItem.second;
          auto minimalPossibleValue = minimalPossibleCurrentGameConfiguration[currentConfigurationItem.first];

          if(currentItemCurrentValue > minimalPossibleValue) {
            minimalPossibleCurrentGameConfiguration[currentConfigurationItem.first] = currentItemCurrentValue;
          }
        }
      }

      auto currentPower = minimalPossibleCurrentGameConfiguration["red"] * minimalPossibleCurrentGameConfiguration["green"] * minimalPossibleCurrentGameConfiguration["blue"];
      totalPowerSum += currentPower;

      int count =
          std::count(invalidGameIds.begin(), invalidGameIds.end(), gameId);
      if (count == 0) {
        validGameIds.push_back(gameId);
      } else {
        std::cout << "game is valid" << std::endl;
      }
    }
  }

  return totalPowerSum;
}
