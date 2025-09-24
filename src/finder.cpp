#include "../include/finder.hpp"
#include <istream>
#include <regex>
#include <vector>

namespace Finder {
std::vector<FinderResult>
RegexFinder::find_in_stream(std::istream &input_stream, std::regex pattern) {
  std::vector<FinderResult> results;
  std::string line;
  uint32_t line_count = 0;
  while (std::getline(input_stream, line)) {
    line_count++;
    std::smatch match;
    std::regex_search(line, match, pattern);
    if (match.empty()) {
      continue;
    };

    results.push_back(FinderResult{
        .line_number = line_count, .match_result = match, .line = line});
  }
  return results;
};
} // namespace Finder
