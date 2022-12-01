#include <fstream>
#include <iostream>
#include <optional>

template <typename T>
void LogVectorLines(std::vector<T>& lines) {
  if constexpr (std::is_same_v<T, std::optional<int>>) {
    for (auto& line : lines) {
      if (line.has_value()) {
        std::cout << line.value() << std::endl;
      } else {
        std::cout << " " << std::endl;
      }
    }
  } else {
    for (auto& line : lines) {
      std::cout << line << std::endl;
    }
  }
}
