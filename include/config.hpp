#pragma once
#include <string>
#include <vector>
namespace Config {

struct Config {
  bool case_insensitive;
  bool show_line_numbers;
  std::vector<std::string> files;
};

class ConfigManager {
public:
  ConfigManager(int argc, char *argv[]);
  ~ConfigManager();

  Config get_config();
  std::string get_pattern();
  std::vector<std::string> *get_file_pathes();

private:
  Config _config;
  std::string _pattern;
  std::vector<std::string> _files;
};
} // namespace Config
