#include "../include/config.hpp"
#include <cctype>
#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <ios>
#include <regex>
#include <set>
#include <string>
#include <sys/stat.h>
#include <unordered_set>
using namespace std;

namespace Config {

bool is_text_file(std::filesystem::path path);

const std::unordered_set<string> binary_extensions = {
    ".exe", ".dll", ".mp3", ".mp4", ".so",  ".bin",
    ".png", ".gif", ".zip", ".pdf", ".tar", ".gz"};

const set<string> known_flags = {
    "-i", // ignore case
    "--ignore-case",
    "-n", // show line numbers
    "--line-number",
    "-c", // suppres normal output & show count of matching lines
    "--count",
    "-r", // Recursively go through files
    "--recursive"};

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

      if (args[i] == "-r" || args[i] == "--recursive") {
        this->_config.recursive = true;
      };

      continue;
    }

    std::filesystem::path path = args[i];
    if (path.has_extension() &&
        binary_extensions.contains(path.extension().string()))
      continue;

    if (std::filesystem::is_directory(path)) {
      this->read_dir_recursive(path, this->_files);
    } else {
      _files.push_back(args[i]);
    }
  }
}

ConfigManager::~ConfigManager() = default;

Config ConfigManager::get_config() { return this->_config; }
string ConfigManager::get_pattern() { return this->_pattern; }
regex_constants::syntax_option_type ConfigManager::get_enabled_regex_flags() {
  return this->_regex_flags;
}

vector<std::filesystem::path> *ConfigManager::get_file_pathes() {
  return &this->_files;
}

void ConfigManager::read_dir_recursive(
    std::filesystem::path dir, std::vector<std::filesystem::path> &target) {

  for (auto &entry : std::filesystem::directory_iterator(dir)) {
    if (entry.is_directory()) {
      read_dir_recursive(entry, target);
    } else {
      if (is_text_file(entry)) {
        target.push_back(entry);
      }
    }
  }
}

bool is_text_file(std::filesystem::path path) {
  std::ifstream file(path, std::ios::binary);
  if (!file)
    return false;
  char buff[8192];
  file.read(buff, sizeof(buff));
  std::streamsize n = file.gcount();
  int printable_chars = 0;
  for (std::streamsize i = 0; i < n; ++i) {
    unsigned char c = buff[i];
    if (c == 0)
      return false; // This is a null byte
    if (isprint(c) || isspace(c)) {
      printable_chars++;
    };
  }
  double ratio = static_cast<double>(printable_chars) / n;
  return ratio > 0.8; // If printable characters are more than 80% it's most
                      // probably a text file
}

}; // namespace Config
