#include <iostream>
#include <optional>

template <typename T>
void LogVectorLines(std::vector<T>& lines) {
  for (auto& line : lines) {
    if constexpr (std::is_same_v<T, std::optional<typename T::value_type>>) {
      if (line.has_value()) {
        std::cout << line.value() << std::endl;
      } else {
        std::cout << " " << std::endl;
      }
    } else {
      std::cout << line << std::endl;
    }
  }
}
