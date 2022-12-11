#include <utility>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/Tokenize.cpp"

// TODO: generalize? and move to helpers library
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
  std::vector<std::shared_ptr<Node>> foldersFlat;

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
              foldersFlat.push_back(child);
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

              // Add size to parent
              auto tempNode = fileSystem;
              // Add size to all parents
              while (tempNode->parent != nullptr) {
                // is likely always true
                if (tempNode->type == NodeType::Folder) {
                  tempNode->size += size;
                }
                tempNode = tempNode->parent;
              }
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

  int sumSize = 0;
  for (const auto& folder : foldersFlat) {
    if (folder->size < 100000) {
      sumSize += folder->size;
    }
  }

  return sumSize;
}

int runPart2(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  std::shared_ptr<Node> fileSystem;
  std::vector<std::shared_ptr<Node>> foldersFlat;

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
              foldersFlat.push_back(child);
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

              // Add size to parent
              auto tempNode = fileSystem;
              // Add size to all parents
              do {
                // is likely always true
                if (tempNode->type == NodeType::Folder) {
                  tempNode->size += size;
                }
                if (tempNode->parent) {
                  tempNode = tempNode->parent;
                }
              } while (tempNode->parent != nullptr);
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

  int totalSizeFixed = 0;
  int TOTAL_DISK_SPACE_AVAILABLE = 70000000;
  int SPACE_NEEDED = 30000000;

  for (auto child : fileSystem->children) {
    totalSizeFixed += child->size;
  }

  int diskSpaceAvailable = TOTAL_DISK_SPACE_AVAILABLE - totalSizeFixed;
  int spaceToFree = SPACE_NEEDED - diskSpaceAvailable;

  int sumSize = 0;
  for (const auto& folder : foldersFlat) {
    if (folder->size < 100000) {
      sumSize += folder->size;
    }
  }

  // add root dir
  fileSystem->size = totalSizeFixed;
  foldersFlat.push_back(fileSystem);

  // sort by size descending
  std::sort(
      foldersFlat.begin(),
      foldersFlat.end(),
      [](const auto& a, const auto& b) { return a->size < b->size; }
  );

  std::shared_ptr<Node> folderToDelete;
  for (const auto& folder : foldersFlat) {
    if (folder->size >= spaceToFree) {
      folderToDelete = folder;
      break;
    }
  }

  return folderToDelete->size;
}
