#include <cctype>
#include <cstddef>
#include <iostream>
#include <istream>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "../include/config.hpp"
#include "../include/debug_logger.hpp"
#include "../include/finder.hpp"
#include "../include/input.hpp"
#include "../include/output.hpp"

using namespace std;

typedef struct args_config {
  bool case_insensetive;
  bool show_line_numbers;
} args_config;

int main(int argc, char *argv[]) {
  DebugLogger::log("Start the App\n");
  auto config_manager = std::make_unique<Config::ConfigManager>(argc, argv);
  Config::Config config = config_manager->get_config();
  auto input_mngr = make_unique<Input::InputManager>();
  auto output_strategy =
      std::make_unique<Output::ConsoleOutput>(Output::OutputConfig{});

  Finder::FinderConfig finder_config = {.mode = Finder::Mode::Normal};
  auto regex_finder = std::make_unique<Finder::RegexFinder>(finder_config);

  vector<string> *file_paths = config_manager->get_file_pathes();
  vector<unique_ptr<istream>> streams =
      input_mngr->get_input_streams(file_paths);
  DebugLogger::log("Streams count:", streams.size());

  string pattern = config_manager->get_pattern();
  DebugLogger::log("Pattern:", pattern);

  std::regex regex_ptrn(pattern, config_manager->get_enabled_regex_flags());

  for (auto &s : streams) {
    vector<Finder::FinderResult> find_res =
        regex_finder->find_in_stream(*s, regex_ptrn);

    if (config.count_mode == true) {
      output_strategy->write(to_string(find_res.size()));
    } else {
      for (auto fr : find_res) {
        output_strategy->write(to_string(fr.line_number));
        output_strategy->write(": ");
        output_strategy->write(fr.line);
      }
    }
  }
}
