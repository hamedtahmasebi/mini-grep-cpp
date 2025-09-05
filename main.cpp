#include <algorithm>
#include <cctype>
#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

#include "debug_logger.hpp"

using namespace std;

typedef struct args_config {
  bool case_insensetive;
  bool show_line_numbers;
} args_config;

args_config read_args(int argc, char *argv[]);
void str_to_lower(string *str);

int main(int argc, char *argv[]) {
  char *file_path = argv[1];
  string pattern = argv[2];

  args_config config = read_args(argc, argv);
  DebugLogger::log("Searching for ", pattern, " in ", file_path, "\n");

  ifstream input_file(file_path);

  if (!input_file.is_open()) {
    cerr << "Error while trying to open the file" << endl;
    return 1;
  }

  vector<string> content;
  string line;
  while (getline(input_file, line)) {
    content.push_back(line);
  }
  for (size_t i = 1; i <= content.size(); ++i) {
    if (config.case_insensetive) {
      str_to_lower(&pattern);
    }
    string line = content[i - 1];

    if (config.case_insensetive) {
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

  input_file.close();
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
