#include <string>
#include <vector>
#include <algorithm>
#include <iterator>

/**
 * @brief Splits a string into tokens based on a provided separator and trims the tokens.
 *
 * The function `splitString` takes a string and a character separator. It splits
 * the string into a series of substrings (tokens), each of which is separated by the
 * separator character. Each token is trimmed to remove leading and trailing whitespace
 * characters. The resulting tokens are stored in a vector and returned.
 *
 * @param str The string to be split and trimmed.
 * @param separator The character used as a separator.
 * @return std::vector<std::string> A vector of trimmed tokenized substrings.
 *
 * Example:
 *
 *   std::string text = "  Hello, world!  Welcome   to C++  ";
 *   char separator = ' ';
 *   std::vector<std::string> tokens = splitString(text, separator);
 *
 *   // The 'tokens' vector will contain: ["Hello,", "world!", "Welcome", "to", "C++"]
 */
std::vector<std::string> splitString(std::string str, char separator) {
  std::vector<std::string> tokens;
  std::string::size_type start = 0;
  auto end = str.find(separator, start);

  auto trim = [](const std::string& s) {
    auto first = std::find_if_not(s.begin(), s.end(), [](unsigned char ch) { return std::isspace(ch); });
    auto last = std::find_if_not(s.rbegin(), s.rend(), [](unsigned char ch) { return std::isspace(ch); }).base();
    return (first < last) ? std::string(first, last) : std::string();
  };

  while (end != std::string::npos) {
    std::string token = trim(str.substr(start, end - start));
    if (!token.empty()) {
      tokens.push_back(token);
    }
    start = end + 1;
    end = str.find(separator, start);
  }

  // Handle the last token
  std::string last_token = trim(str.substr(start));
  if (!last_token.empty()) {
    tokens.push_back(last_token);
  }

  return tokens;
}
