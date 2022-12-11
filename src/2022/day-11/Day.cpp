#include <cmath>
#include <utility>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/Tokenize.cpp"

class Monkey;

struct TestAction {
  int divisibleBy;
  std::shared_ptr<Monkey> positive;
  std::shared_ptr<Monkey> negative;
};

enum class Operator { Multiply, Add };

struct Operation {
  std::string left;
  std::string right;
  Operator op;
};

class Monkey {
 public:
  int inspectedItemsCount = 0;
  std::string name;
  std::vector<int> items = {};
  Operation operation = {
      .left = "",
      .right = "",
      .op = Operator::Multiply,
  };
  TestAction testAction{
      0,
      nullptr,
      nullptr,
  };

  int operationSideToInt(const std::string& side, int item) {
    if (side == "old") {
      return item;
    }

    return std::stoi(side);
  }

  int executeOperation(int item) {
    switch (operation.op) {
      case Operator::Multiply:
        return operationSideToInt(operation.left, item) *
               operationSideToInt(operation.right, item);
      case Operator::Add:
        return operationSideToInt(operation.left, item) +
               operationSideToInt(operation.right, item);
    }
  }

  void inspectItems() {
    while (!items.empty()) {
      int item = items.front();
      items.erase(items.begin());

      int newItem = std::floor(executeOperation(item) / 3);
      inspectedItemsCount += 1;

      if (newItem % testAction.divisibleBy == 0) {
        testAction.positive->items.emplace_back(newItem);
      } else {
        testAction.negative->items.emplace_back(newItem);
      }
    }
  }
};

std::vector<std::shared_ptr<Monkey>> parseFileCreateMonkeys(
    std::vector<std::optional<std::string>> lines
) {
  std::vector<std::shared_ptr<Monkey>> monkeys;

  // initialize all monkeys
  for (auto line : lines) {
    if (!line.has_value()) {
      continue;
    }

    if (line.value().starts_with("Monkey")) {
      auto monkey = std::make_shared<Monkey>();
      monkeys.push_back(monkey);
    }

    if (line.value().starts_with("  Starting items")) {
      auto monkey = monkeys.back();
      auto itemsString = line.value().substr(17);
      auto tokens = tokenize(itemsString, ", ");
      for (const auto& token : tokens) {
        monkey->items.push_back(std::stoi(token));
      }
    }

    if (line.value().starts_with("  Operation:")) {
      auto monkey = monkeys.back();
      auto operationString = line.value().substr(13);

      auto operationStringRightSide =
          operationString.substr(operationString.find("=") + 1);
      Operator op = operationString.find("*") != std::string::npos
                        ? Operator::Multiply
                        : Operator::Add;

      if (op == Operator::Multiply) {
        auto tokens = tokenize(operationStringRightSide, " * ");
        monkey->operation = {
            .left = tokens[0],
            .right = tokens[1],
            .op = op,
        };
      } else {
        auto tokens = tokenize(operationStringRightSide, " + ");
        monkey->operation = {
            .left = tokens[0],
            .right = tokens[1],
            .op = op,
        };
      }
    }

    if (line.value().starts_with("  Test:")) {
      auto monkey = monkeys.back();

      auto divisibleBy = line.value().substr(21);
      monkey->testAction.divisibleBy = std::stoi(divisibleBy);
      ;
    }
  }

  // initialize throw to references
  int monkeyIndex = 0;
  for (auto line : lines) {
    if (!line.has_value()) {
      continue;
    }

    auto monkey = monkeys[monkeyIndex];
    monkey->name = std::to_string(monkeyIndex);

    if (line.value().starts_with("    If true: throw to monkey ")) {
      auto monkey = monkeys[monkeyIndex];
      auto throwToIndex = line.value().substr(29);

      auto targetMonkey = monkeys[std::stoi(throwToIndex)];
      monkey->testAction.positive = targetMonkey;
    }

    if (line.value().starts_with("    If false: throw to monkey ")) {
      auto monkey = monkeys[monkeyIndex];
      auto throwToIndex = line.value().substr(30);

      auto targetMonkey = monkeys[std::stoi(throwToIndex)];
      monkey->testAction.negative = targetMonkey;
      monkeyIndex++;
    }
  }

  return monkeys;
}

void playRound(std::vector<std::shared_ptr<Monkey>> monkeys) {
  for (auto monkey : monkeys) {
    monkey->inspectItems();
  }
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);
  auto monkeys = parseFileCreateMonkeys(lines);

  for (int i = 0; i < 20; i++) {
    playRound(monkeys);
  }

  for (auto monkey : monkeys) {
    // log inspected count
    std::cout << "Monkey " << monkey->name << " inspected items "
              << monkey->inspectedItemsCount << " times." << std::endl;
  }

  std::sort(monkeys.begin(), monkeys.end(), [](const auto& a, const auto& b) {
    return a->inspectedItemsCount > b->inspectedItemsCount;
  });

  std::cout << "Two most active monkeys inspected items: " << monkeys[0]->inspectedItemsCount << " and " << monkeys[1]->inspectedItemsCount << std::endl;

  int levelOfMonkeyBusiness =
      monkeys[0]->inspectedItemsCount * monkeys[1]->inspectedItemsCount;

  std::cout << "Level of monkey business: " << levelOfMonkeyBusiness << std::endl;

  return levelOfMonkeyBusiness;
}
