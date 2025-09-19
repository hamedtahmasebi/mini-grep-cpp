#pragma once
#include <regex>
#include <string>
#include <vector>
namespace Config {

struct Config {
  bool case_insensitive;
  bool show_line_numbers;
  bool count_mode;
  std::vector<std::string> files;
};

class ConfigManager {
public:
  ConfigManager(int argc, char *argv[]);
  ~ConfigManager();

  Config get_config();
  std::string get_pattern();
  std::vector<std::string> *get_file_pathes();
  std::regex_constants::syntax_option_type get_enabled_regex_flags();

private:
  Config _config;
  std::string _pattern;
  std::vector<std::string> _files;
  std::regex_constants::syntax_option_type _regex_flags;
};
} // namespace Config
