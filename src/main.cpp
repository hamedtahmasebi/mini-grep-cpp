#include <cctype>
#include <cstddef>
#include <filesystem>
#include <memory>
#include <regex>
#include <string>
#include <vector>

#include "../include/config.hpp"
#include "../include/finder.hpp"
#include "../include/input.hpp"
#include "../include/output.hpp"

using namespace std;

typedef struct args_config {
  bool case_insensetive;
  bool show_line_numbers;
} args_config;

int main(int argc, char *argv[]) {
  auto config_manager = std::make_unique<Config::ConfigManager>(argc, argv);
  Config::Config config = config_manager->get_config();
  auto input_mngr = make_unique<Input::InputManager>();
  auto output_strategy =
      std::make_unique<Output::ConsoleOutput>(Output::OutputConfig{});

  Finder::FinderConfig finder_config = {.mode = Finder::Mode::Normal};
  auto regex_finder = std::make_unique<Finder::RegexFinder>(finder_config);

  vector<std::filesystem::path> *file_paths = config_manager->get_file_pathes();
  vector<Input::InputObject> inputs =
      input_mngr->get_input_streams(*file_paths);

  string pattern = config_manager->get_pattern();

  std::regex regex_ptrn(pattern, config_manager->get_enabled_regex_flags());

  for (const auto &inp : inputs) {
    const auto find_res = regex_finder->find_in_stream(*inp.stream, regex_ptrn);
    const bool should_show_filename = inputs.size() > 1 && !find_res.empty();
    if (config.count_mode == true) {
      if (should_show_filename) {
        output_strategy->write(inp.name + ": ");
      }
      output_strategy->write_line(to_string(find_res.size()));
    } else {

      if (should_show_filename) {
        output_strategy->write_line(inp.name);
      }
      for (auto fr : find_res) {
        output_strategy->write(to_string(fr.line_number));
        output_strategy->write(": ");
        output_strategy->write_line(fr.line);
      }
    }
  }
}
