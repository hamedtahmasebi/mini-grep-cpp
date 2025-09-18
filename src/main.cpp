#include <cctype>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <istream>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "../include/config.hpp"
#include "../include/debug_logger.hpp"
#include "../include/input.hpp"

using namespace std;

typedef struct args_config {
  bool case_insensetive;
  bool show_line_numbers;
} args_config;

int main(int argc, char *argv[]) {
  DebugLogger::log("Start the App\n");
  Config::ConfigManager *config_manager = new Config::ConfigManager(argc, argv);
  Config::Config config = config_manager->get_config();
  Input::InputManager *input_mngr = new Input::InputManager();

  vector<string> *file_paths = config_manager->get_file_pathes();
  vector<unique_ptr<istream>> streams =
      input_mngr->get_input_streams(file_paths);
  DebugLogger::log("Streams count:", streams.size());

  string pattern = config_manager->get_pattern();

  for (auto &s : streams) {
    vector<string> content;
    string line;

    DebugLogger::log("Config done, start reading\n");
    while (getline(*s, line)) {
      content.push_back(line);
    }
    regex_constants::syntax_option_type flags =
        config_manager->get_enabled_regex_flags();

    for (size_t i = 1; i <= content.size(); ++i) {
      string line = content[i - 1];
      regex re(pattern, flags);
      smatch result;
      regex_search(line, result, re);
      if (result.empty()) {
        continue;
      }
      if (config.show_line_numbers) {
        printf("%zu: ", i);
      }
      printf("%s\n", content[i - 1].c_str());
    }
  }
}
