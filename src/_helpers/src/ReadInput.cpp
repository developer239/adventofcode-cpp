#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

std::vector<std::optional<int>> ReadInput(const std::string& filename) {
  std::ifstream file(filename);
  std::vector<std::optional<int>> input;
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty()) {
      input.emplace_back(std::nullopt);
    } else {
      input.emplace_back(std::stoi(line));
    }
  }
  return input;
}
