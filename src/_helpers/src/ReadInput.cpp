#include <fstream>
#include <iostream>
#include <optional>
#include <vector>

template <typename T>
concept IsText = std::is_same_v<T, std::string>;

template <typename T>
concept IsNumber = std::is_same_v<T, int>;

template <typename T>
  requires IsText<T> || IsNumber<T>
auto ReadInput(const std::string& filename) {
  std::ifstream file(filename);

  if (!file.is_open()) {
    std::cout << "Could not open file: " << filename << std::endl;
    exit(1);
  }

  std::vector<std::optional<T>> input;
  std::string line;

  while (std::getline(file, line)) {
    if (line.empty()) {
      input.emplace_back(std::nullopt);
    } else {
      if constexpr (IsText<T>) {
        input.emplace_back(line);
      } else if constexpr (IsNumber<T>) {
        input.emplace_back(std::stoi(line));
      }
    }
  }

  return input;
}
