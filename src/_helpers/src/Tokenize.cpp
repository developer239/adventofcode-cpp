#include <fstream>
#include <vector>

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