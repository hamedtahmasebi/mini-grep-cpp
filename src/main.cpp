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
#include "../include/output.hpp"

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
  Output::OutputStrategy *output_strategy =
      new Output::ConsoleOutput(Output::OutputConfig{
          .mode = config.count_mode ? Output::OutputMode::Count
                                    : Output::OutputMode::Normal

      });

  vector<string> *file_paths = config_manager->get_file_pathes();
  vector<unique_ptr<istream>> streams =
      input_mngr->get_input_streams(file_paths);
  DebugLogger::log("Streams count:", streams.size());

  string pattern = config_manager->get_pattern();
  DebugLogger::log("Pattern:", pattern);
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
        // TODO: output constraints should be handled better. preferably in
        // OutputStrategy
        output_strategy->write_line(to_string(i) + ": " + content[i - 1]);
      }
      output_strategy->write_line(content[i - 1]);
    }
  }
}
