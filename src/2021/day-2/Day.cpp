#include <numeric>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

std::string FORWARD = "forward";
std::string UP = "up";
std::string DOWN = "down";

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int x = 0;
  int y = 0;

  for (auto line : lines) {
    if (line.has_value()) {
      if (line->starts_with(FORWARD)) {
        auto value = line->substr(FORWARD.length());
        x += std::stoi(value);
      }

      if (line->starts_with(UP)) {
        auto value = line->substr(UP.length());
        y -= std::stoi(value);;
      }

      if (line->starts_with(DOWN)) {
        auto value = line->substr(DOWN.length());
        y += std::stoi(value);
      }
    }
  }

  return x * y;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int x = 0;
  int y = 0;
  int aim = 0;

  for (auto line : lines) {
    if (line.has_value()) {
      if (line->starts_with(FORWARD)) {
        auto value = line->substr(FORWARD.length());
        x += std::stoi(value);
        y += aim * std::stoi(value);
      }

      if (line->starts_with(UP)) {
        auto value = line->substr(UP.length());
        aim -= std::stoi(value);
      }

      if (line->starts_with(DOWN)) {
        auto value = line->substr(DOWN.length());
        aim += std::stoi(value);
      }
    }
  }

  return x * y;
}
