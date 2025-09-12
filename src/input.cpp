#include "../include/input.hpp"
#include "../include/debug_logger.hpp"
#include <fstream>
#include <iostream>
#include <istream>
#include <memory>
#include <string>
#include <sys/stat.h>
using namespace std;

namespace Input {

InputManager::InputManager() {
  struct stat st;
  fstat(STDIN_FILENO, &st);
  this->is_stdin_piped = !S_ISCHR(st.st_mode);
};
InputManager::~InputManager() = default;

vector<unique_ptr<istream>>
InputManager::get_input_streams(vector<string> *files) {
  vector<unique_ptr<istream>> res;
  if (this->is_stdin_piped) {
    DebugLogger::log("Reading from cin \n");
    res.push_back(make_unique<istream>(cin.rdbuf()));
    return res;
  };
  if (files->empty())
    return res;

  for (auto &f : *files) {
    DebugLogger::log("Reading from file:", f, "\n");
    res.push_back(make_unique<ifstream>(f));
  }

  return res;
};

bool is_stdin_piped;
}; // namespace Input
