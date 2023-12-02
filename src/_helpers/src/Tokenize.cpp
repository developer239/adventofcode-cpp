#include <fstream>
#include <vector>

/**
 * @brief Splits a string into tokens based on the provided delimiters.
 *
 * The function `tokenize` takes a string and a set of delimiter characters.
 * It then scans the string and splits it into a series of substrings (tokens),
 * each of which is separated by at least one of the delimiter characters.
 * The resulting tokens are stored in a vector and returned.
 *
 * @param str The string to be tokenized.
 * @param delimiters A string containing all delimiter characters.
 * @return std::vector<std::string> A vector of tokenized substrings.
 *
 * Example:
 *
 *   std::string text = "Hello, world! Welcome to C++ programming.";
 *   std::string delims = " ,!."; // Delimiters are space, comma, exclamation, and period
 *   std::vector<std::string> tokens = tokenize(text, delims);
 *
 *   // The 'tokens' vector will contain: ["Hello", "world", "Welcome", "to", "C++", "programming"]
 */
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
