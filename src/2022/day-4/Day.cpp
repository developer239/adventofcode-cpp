#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

std::vector<std::pair<int, int>> lineToRanges(std::optional<std::string>& line
) {
  int leftStart, leftEnd, rightStart, rightEnd;
  sscanf(
      line.value().c_str(),
      "%d-%d,%d-%d",
      &leftStart,
      &leftEnd,
      &rightStart,
      &rightEnd
  );

  std::vector<std::pair<int, int>> ranges = {
      {leftStart, leftEnd},
      {rightStart, rightEnd}};

  return ranges;
}

// TODO: consider using something like this:
// #include <aoc.hpp>
//
// namespace detail {
//  using point = aoc::point<i32, 2>;
//
//  auto const parse = [](auto const& line) -> std::pair<point, point> {
//    point a;
//    point b;
//    (void)scn::scan(line, "{}-{},{}-{}", a[0], a[1], b[0], b[1]);
//    return {a,b};
//  };
//
//  template<bool B = true>
//    auto contains(std::pair<point, point> p) -> bool {
//      auto [a, b] = p;
//      return (a[0] <= b[0] && a[1] >= b[1]) || (B && contains<!B>({b, a}));
//    };
//
//  template<bool B = true>
//    auto overlaps(std::pair<point, point> p) -> bool {
//      auto [a, b] = p;
//      return (a[0] <= b[0] && a[1] >= b[0]) || (B && overlaps<!B>({b, a}));
//    };
//} // namespace detail
//
// template<>
//  auto advent2022::day04() -> result {
//    auto pairs = lz::map(aoc::util::readlines("./source/2022/04/input.txt"),
//    detail::parse).toVector(); auto part1 =
//    std::transform_reduce(pairs.begin(), pairs.end(), u64{0}, std::plus{},
//    detail::contains<true>); auto part2 = std::transform_reduce(pairs.begin(),
//    pairs.end(), u64{0}, std::plus{}, detail::overlaps<true>); return
//    aoc::result(part1, part2);
//  }

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int sumFullyOverlappingPairs = 0;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];

    if (line.has_value()) {
      std::vector<std::pair<int, int>> ranges = lineToRanges(line);

      auto firstRange = ranges[0];
      auto secondRange = ranges[1];

      if (firstRange.first >= secondRange.first &&
          firstRange.second <= secondRange.second) {
        sumFullyOverlappingPairs++;
      } else if (secondRange.first >= firstRange.first && secondRange.second <= firstRange.second) {
        sumFullyOverlappingPairs++;
      }
    }
  }

  return sumFullyOverlappingPairs;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  int sumPartiallyOverlappingPairs = 0;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];

    if (line.has_value()) {
      std::vector<std::pair<int, int>> ranges = lineToRanges(line);

      auto leftStart = ranges[0].first;
      auto leftEnd = ranges[0].second;
      auto rightStart = ranges[1].first;
      auto rightEnd = ranges[1].second;

      if (leftStart >= rightStart && leftStart <= rightEnd) {
        sumPartiallyOverlappingPairs++;
      } else if (leftEnd >= rightStart && leftEnd <= rightEnd) {
        sumPartiallyOverlappingPairs++;
      } else if (rightStart >= leftStart && rightStart <= leftEnd) {
        sumPartiallyOverlappingPairs++;
      } else if (rightEnd >= leftStart && rightEnd <= leftEnd) {
        sumPartiallyOverlappingPairs++;
      }
    }
  }

  return sumPartiallyOverlappingPairs;
}
