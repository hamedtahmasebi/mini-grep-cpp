#include "../include/config.hpp"
#include <set>
#include <string>
#include <sys/stat.h>
using namespace std;

namespace Config {

const set<string> known_flags = {
    "-i", // case insensitive
    "-n"  // show line numbers
};

ConfigManager::ConfigManager(int argc, char *argv[]) {
  vector<string> args(argv, argv + argc);
  this->_pattern = args[1];
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
    _files.push_back(args[i]);
  }
}

ConfigManager::~ConfigManager() = default;

Config ConfigManager::get_config() { return this->_config; }
string ConfigManager::get_pattern() { return this->_pattern; }
vector<string> *ConfigManager::get_file_pathes() { return &this->_files; }

Config _config;
string _pattern;
vector<string> _files;
}; // namespace Config
