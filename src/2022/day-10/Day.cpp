#include <queue>
#include <utility>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  std::queue<int> tasks;
  int importantCycleNumber = 20;

  int x = 1;
  int cycleNumber = 1;
  int taskCyclesCompleted = 0;
  int signalStrength = 0;
  while (cycleNumber <= lines.size() || !tasks.empty()) {
    auto line = lines[cycleNumber - 1];
    auto entry = line.has_value() ? line.value() : "";

    if (entry.starts_with("noop")) {
      tasks.push(0);
    } else if (entry.starts_with("addx")) {
      auto value = std::stoi(entry.substr(5));
      tasks.push(value);
    }

    if (cycleNumber == importantCycleNumber) {
      signalStrength += cycleNumber * x;

      importantCycleNumber += 40;
    }

    cycleNumber++;
    if (!tasks.empty()) {
      taskCyclesCompleted++;

      // handle noop
      auto firstValue = tasks.front();
      if (firstValue == 0) {
        tasks.pop();
        taskCyclesCompleted = 0;
      }
      // handle addx
      if (taskCyclesCompleted == 2) {
        x += tasks.front();
        tasks.pop();
        taskCyclesCompleted = 0;
      }
    }
  }

  return signalStrength;
}

class Buffer {
 public:
  uint8_t * colorBuffer = (uint8_t *)malloc(sizeof(uint8_t ) * 40 * 6);

  ~Buffer() { free(colorBuffer); }

  void drawAtPosition(int position) { colorBuffer[position] = 1; }

  void coutASCII() {
    for (int i = 0; i < 40 * 6; i++) {
      if (i % 40 == 0) {
        std::cout << std::endl;
      }
      if (colorBuffer[i] == 1) {
        std::cout << "#";
      } else {
        std::cout << ".";
      }
    }
  }
};

void runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  auto buffer = Buffer();

  std::queue<int> tasks;

  std::vector<int> spritePosition = {0, 1, 2};

  int x = 1;
  int cycleNumber = 1;
  int taskCyclesCompleted = 0;
  while (cycleNumber <= lines.size() || !tasks.empty()) {
    auto line = lines[cycleNumber - 1];
    auto entry = line.has_value() ? line.value() : "";

    if (entry.starts_with("noop")) {
      tasks.push(0);
    } else if (entry.starts_with("addx")) {
      auto value = std::stoi(entry.substr(5));
      tasks.push(value);
    }

    if (!tasks.empty()) {
      taskCyclesCompleted++;

      // handle noop
      auto firstValue = tasks.front();
      if (firstValue == 0) {
        tasks.pop();
        taskCyclesCompleted = 0;
      }
      // handle addx
      if (taskCyclesCompleted == 2) {
        x += tasks.front();
        tasks.pop();
        taskCyclesCompleted = 0;
      }
    }

    int offset = 0;
    if (cycleNumber < 40) {
      offset = 0;
    } else if (cycleNumber < 80) {
      offset = 40;
    } else if (cycleNumber < 120) {
      offset = 80;
    } else if (cycleNumber < 160) {
      offset = 120;
    } else if (cycleNumber < 200) {
      offset = 160;
    } else if (cycleNumber < 240) {
      offset = 200;
    }

    int normalizedSpritePosition = offset + x;
    spritePosition = {
        normalizedSpritePosition - 1,
        normalizedSpritePosition,
        normalizedSpritePosition + 1};
    bool isCycleInSpritePosition =
        find(spritePosition.begin(), spritePosition.end(), cycleNumber) !=
        spritePosition.end();

    if (isCycleInSpritePosition) {
      buffer.drawAtPosition(cycleNumber);
    }
    cycleNumber++;
  }

  buffer.coutASCII();
}
