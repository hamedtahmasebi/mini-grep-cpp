#include "debug_logger.hpp"
#include <set>
#include <string>
#include <sys/stat.h>

using namespace std;

namespace Config {

typedef struct Config {
  bool case_insensitive;
  bool show_line_numbers;
  vector<string> files;
} Config;

const set<string> known_flags = {
    "-i", // case insensitive
    "-n"  // show line numbers
};

class ConfigManager {
public:
  ConfigManager(int argc, char *argv[]) {
    vector<string> args(argv, argv + argc);
    this->pattern = args[1];
    for (size_t i = 2; i < args.size(); ++i) {
      if (args[i].starts_with("-") && known_flags.contains(args[i])) {
        if (args[i] == "-i") {
          this->_config.case_insensitive = true;
          continue;
        }

        if (args[i] == "-n") {
          this->_config.show_line_numbers = true;
          continue;
        }

        continue;
      }
      files.push_back(args[i]);
    }
  };
  ~ConfigManager() = default;

  Config get_config() { return this->_config; }
  string get_pattern() { return this->pattern; }
  vector<string> *get_file_pathes() { return &this->files; }

private:
  Config _config;
  string pattern;
  vector<string> files;
};

} // namespace Config
