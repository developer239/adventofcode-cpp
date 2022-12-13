#include <algorithm>
#include <charconv>
#include <iostream>
#include <utility>
#include <variant>
#include <vector>

#include "src/LogVectorLines.cpp"
#include "src/ReadInput.cpp"
#include "src/Tokenize.cpp"

// I decided to repurpose someone else's code for this one because I wasn't sure how to work with variants
// https://github.com/progheal/adventofcode/blob/master/2022/13.cpp

struct Value : public std::variant<int, std::vector<Value>> {
  Value(int v) : variant(v) {}
  Value(const std::vector<Value>& v) : variant(v) {}
  bool operator<(const Value& rhs) const;
};

struct CompareVisitor {
  bool operator()(int l, int r) const { return l < r; }
  bool operator()(const std::vector<Value>& l, const std::vector<Value>& r)
      const {
    return lexicographical_compare(l.begin(), l.end(), r.begin(), r.end());
  }
  bool operator()(int l, const std::vector<Value>& r) const {
    return operator()(std::vector<Value>{l}, r);
  }
  bool operator()(const std::vector<Value>& l, int r) const {
    return operator()(l, std::vector<Value>{r});
  }
} compareVisitor;

bool Value::operator<(const Value& rhs) const {
  return std::visit(compareVisitor, *this, rhs);
}

struct PrintVisitor {
  std::ostream& out;
  void operator()(int value) const { out << value; }
  void operator()(const std::vector<Value>& value) const {
    bool first = true;
    for (auto& child : value) {
      out << (first ? "[" : ",");
      std::visit(*this, child);
      first = false;
    }
    if (first) {
      out << "[";
    }
    out << "]";
  }
};

std::ostream& operator<<(std::ostream& out, const Value& v) {
  std::visit(PrintVisitor{out}, v);
  return out;
}

Value parse(std::string& string) {
  if (string[0] == '[') {
    std::vector<Value> result;
    if (string[1] != ']') {
      while (string[0] != ']') {
        string = string.substr(1);
        result.push_back(parse(string));
      }
      string = string.substr(1);
    } else {
      string = string.substr(2);
    }
    return result;
  } else {
    int value;
    auto p =
        std::from_chars(string.data(), string.data() + string.size(), value);
    string = string.substr(p.ptr - string.data());
    return value;
  }
}

long runPart1(const std::string& filename) {
  auto lines = ReadInput<std::string>(filename);

  std::vector<Value> all;
  int indicesSum = 0;

  for (int index = 0; index < lines.size(); index++) {
    auto line = lines[index];
    if (line.has_value()) {
      Value value = parse(line.value());
      all.push_back(value);

      if (filename.find("example") != std::string::npos) {
        std::cerr << value << std::endl;
      }

      if (all.size() % 2 == 0) {
        if (all[all.size() - 2] < all.back()) {
          indicesSum += (all.size() / 2);
        }
      }
    }
  }

  return indicesSum;
}
