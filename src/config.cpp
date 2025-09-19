#include "../include/config.hpp"
#include <regex>
#include <set>
#include <string>
#include <sys/stat.h>
using namespace std;

namespace Config {

const set<string> known_flags = {
    "-i", // ignore case
    "--ignore-case",
    "-n", // show line numbers
    "--line-number",
    "-c", // suppres normal output & show count of matching lines
    "--count"};

ConfigManager::ConfigManager(int argc, char *argv[])
    : _regex_flags(regex_constants::ECMAScript) {
  vector<string> args(argv, argv + argc);
  this->_pattern = args[1];
  for (size_t i = 2; i < args.size(); ++i) {
    if (args[i].starts_with("-") && known_flags.contains(args[i])) {
      if (args[i] == "-i" || args[i] == "--ignore-case") {
        this->_config.case_insensitive = true;
        this->_regex_flags |= regex_constants::icase;
        continue;
      }

      if (args[i] == "-n" || args[i] == "--line-number") {
        this->_config.show_line_numbers = true;
        continue;
      }

      if (args[i] == "-c" || args[i] == "--count") {
        this->_config.count_mode = true;
        continue;
      }

      continue;
    }
    _files.push_back(args[i]);
  }
}

ConfigManager::~ConfigManager() = default;

Config ConfigManager::get_config() { return this->_config; }
string ConfigManager::get_pattern() { return this->_pattern; }
regex_constants::syntax_option_type ConfigManager::get_enabled_regex_flags() {
  return this->_regex_flags;
}

vector<string> *ConfigManager::get_file_pathes() { return &this->_files; }

}; // namespace Config
