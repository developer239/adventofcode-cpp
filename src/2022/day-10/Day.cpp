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

    //    std::cout << "Cycle number: " << cycleNumber << " value: " << x
    //              << std::endl;

    if (cycleNumber == importantCycleNumber) {
      std::cout << "Important cycle number: " << cycleNumber << std::endl;
      std::cout << "Register X has value: " << x << std::endl;

      signalStrength += cycleNumber * x;
      std::cout << "Signal strength: " << signalStrength << std::endl;

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
