#include <numeric>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

int binaryToInteger(const std::vector<int>& binary) {
  int result = 0;
  int power = 0;

  for (int i = binary.size() - 1; i >= 0; i--) {
    auto value = binary[i];
    if (value == 1) {
      result += std::pow(2, power);
    }
    power++;
  }

  return result;
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  auto bitsPerLine = lines[0]->size();

  int oneCount = 0;
  int zeroCount = 0;
  auto gammaRate = std::vector<int>();
  auto epsilonRate = std::vector<int>();

  for (int bitIndex = 0; bitIndex < bitsPerLine; bitIndex++) {
    for (auto line : lines) {
      if (line.has_value()) {
        auto lineValue = line.value();
        auto value = lineValue.at(bitIndex) - '0';
        if (value) {
          oneCount += 1;
        } else {
          zeroCount += 1;
        }
      }
    }

    gammaRate.emplace_back(oneCount > zeroCount);

    oneCount = 0;
    zeroCount = 0;
  }

  for (int bit : gammaRate) {
    epsilonRate.emplace_back(bit == 1 ? 0 : 1);
  }

  auto gammaRateInt = binaryToInteger(gammaRate);
  auto epsilonRateInt = binaryToInteger(epsilonRate);

  return gammaRateInt * epsilonRateInt;
}

std::string calculateRating(std::vector<std::string> lines, int bitIndex, int ratingImportantNumber) {
  if (lines.size() == 1) {
    return lines[0];
  }

  int oneCount = 0;
  int zeroCount = 0;
  auto rate = std::vector<int>();

  for (auto line : lines) {
    auto value = line.at(bitIndex) - '0';
    if (value) {
      oneCount += 1;
    } else {
      zeroCount += 1;
    }
  }

  int toKeep;

  if(ratingImportantNumber == 1) {
    if(oneCount == zeroCount) {
      toKeep = 1;
    } else {
      toKeep = oneCount > zeroCount ? 1 : 0;
    }
  }

  if(ratingImportantNumber == 0) {
    if(oneCount == zeroCount) {
      toKeep = 0;
    } else {
      toKeep = oneCount > zeroCount ? 0 : 1;
    }
  }

  auto linesFiltered = std::vector<std::string>();
  for(auto line: lines) {
    auto lineBitIndexValue = line[bitIndex] - '0';
    if(lineBitIndexValue == toKeep) {
      linesFiltered.emplace_back(line);
    }
  }

  return calculateRating(linesFiltered, bitIndex + 1, ratingImportantNumber);
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  auto linesFiltered = std::vector<std::string>();
  for (auto line : lines) {
    if (line.has_value()) {
      linesFiltered.emplace_back(line.value());
    }
  }

  auto oxygenRating = calculateRating(linesFiltered, 0, 1);
  auto coRating = calculateRating(linesFiltered, 0, 0);

  auto oxygenRatingVec = std::vector<int>();
  auto coRatingVec = std::vector<int>();

  for(auto bit: oxygenRating) {
    oxygenRatingVec.emplace_back(bit - '0');
  }
  for(auto bit: coRating) {
    coRatingVec.emplace_back(bit - '0');
  }

  auto oxygenRatingInt = binaryToInteger(oxygenRatingVec);
  auto coRatingInt = binaryToInteger(coRatingVec);

  return oxygenRatingInt * coRatingInt;
}
