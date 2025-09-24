#include <regex>
#include <vector>
namespace Finder {

enum class Mode {
  Normal,
  Count,
};

struct FinderConfig {
  Mode mode;
};

struct FinderResult {
  uint32_t line_number;
  std::smatch match_result;
  std::string line;
};

class RegexFinder {
public:
  RegexFinder(FinderConfig cfg) : config(cfg) {};
  ~RegexFinder() = default;
  std::vector<FinderResult> find_in_stream(std::istream &input,
                                           std::regex pattern);

private:
  FinderConfig config;
};

} // namespace Finder
