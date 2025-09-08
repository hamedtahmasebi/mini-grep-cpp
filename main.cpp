#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <iostream>
#include <istream>
#include <memory>
#include <string>
#include <vector>

#include "config.cpp"
#include "debug_logger.hpp"
#include "input.cpp"

using namespace std;

typedef struct args_config {
  bool case_insensetive;
  bool show_line_numbers;
} args_config;

args_config read_args(int argc, char *argv[]);
void str_to_lower(string *str);

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
  vector<string> content;
  string line;

  DebugLogger::log("Config done, start reading\n");
  while (getline(*streams[0], line)) {
    content.push_back(line);
  }
  for (size_t i = 1; i <= content.size(); ++i) {
    if (config.case_insensitive) {
      str_to_lower(&pattern);
    }
    string line = content[i - 1];

    if (config.case_insensitive) {
      str_to_lower(&line);
    }
    string::size_type pos = line.find(pattern);
    if (pos == string::npos) {
      continue;
    }
    if (config.show_line_numbers) {
      printf("%zu: ", i);
    }
    printf("%s\n", &content[i][0]);
  }
}

args_config read_args(int argc, char *argv[]) {
  args_config res;
  vector<string> args_vec(argv, argv + argc);
  for (size_t i = 0; i < args_vec.size(); ++i) {
    string arg = args_vec.at(i);
    if (arg == "-i") {
      DebugLogger::log("Flag Enabled -i -> Case insensitive");
      res.case_insensetive = true;
    }
    if (arg == "-n") {
      DebugLogger::log("Flag Enabled -n -> Show line numbers");
      res.show_line_numbers = true;
    }
  }
  return res;
}

void str_to_lower(string *str) {
  transform(str->begin(), str->end(), str->begin(),
            [](unsigned char c) { return tolower(c); });
}
