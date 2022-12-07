#include <utility>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"

std::vector<std::string> tokenize(
    const std::string& str, const std::string& delimiters
) {
  using ssize_t = std::string::size_type;
  const ssize_t str_ln = str.length();
  ssize_t last_pos = 0;

  // container for the extracted tokens
  std::vector<std::string> tokens;

  while (last_pos < str_ln) {
    // find the position of the next delimiter
    ssize_t pos = str.find_first_of(delimiters, last_pos);

    // if no delimiters found, set the position to the length of string
    if (pos == std::string::npos) pos = str_ln;

    // if the substring is nonempty, store it in the container
    if (pos != last_pos)
      tokens.emplace_back(str.substr(last_pos, pos - last_pos));

    // scan past the previous substring
    last_pos = pos + 1;
  }

  return tokens;
}

enum class NodeType {
  File,
  Folder,
};

class Node {
 public:
  NodeType type;
  std::string name;
  int size = 0;

  std::shared_ptr<Node> parent;
  std::vector<std::shared_ptr<Node>> children;

  Node(
      NodeType type, std::string name, std::shared_ptr<Node> parent, int size
  ) {
    this->type = type;
    this->name = name;
    this->parent = parent;
    this->size = size;
  }

  void addChild(const std::shared_ptr<Node>& child) {
    this->children.push_back(child);
  }
};

enum class EntryType {
  Command,
  Output,
};

EntryType getEntryType(const std::string& line) {
  if (line.starts_with("$")) {
    return EntryType::Command;
  } else {
    return EntryType::Output;
  }
}

int runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  std::shared_ptr<Node> fileSystem;

  for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
    auto line = lines[lineIndex];
    auto entry = line.value();

    // Root is always first line
    if (lineIndex == 0) {
      fileSystem = std::make_shared<Node>(NodeType::Folder, "/", nullptr, 0);
      continue;
    }

    // Decide whether command or output
    auto entryType = getEntryType(entry);

    if (entryType == EntryType::Command) {
      // Handle directory navigation
      if (entry.starts_with("$ cd")) {
        auto path = entry.substr(5);

        // Navigate to parent
        if (path == "..") {
          fileSystem = fileSystem->parent;
        }
        // Navigate to child
        else {
          for (const auto& child : fileSystem->children) {
            if (child->name == path) {
              fileSystem = child;
              break;
            }
          }
        }
      }
      // Handle output
      else if (entry.starts_with("$ ls")) {
        lineIndex++;

        // while line is not a command
        while (lines[lineIndex].has_value() &&
               getEntryType(lines[lineIndex].value()) == EntryType::Output) {
          if (lines[lineIndex].has_value()) {
            auto entryNested = lines[lineIndex].value();

            // if directory
            if (entryNested.starts_with("dir")) {
              auto name = entryNested.substr(4);
              auto child =
                  std::make_shared<Node>(NodeType::Folder, name, fileSystem, 0);
              fileSystem->addChild(child);
            }
            // if file
            else {
              auto entryNestedTokens = tokenize(entryNested, " ");
              auto size = std::stoi(entryNestedTokens[0]);
              auto name = entryNestedTokens[1];

              auto child = std::make_shared<Node>(
                  NodeType::File,
                  name,
                  fileSystem,
                  size
              );
              fileSystem->addChild(child);


            }

            lineIndex++;
          }
        }
        lineIndex--;
      }
    }
  }

  // traverse to parent
  while (fileSystem->parent != nullptr) {
    fileSystem = fileSystem->parent;
  }

  return 99;
}
