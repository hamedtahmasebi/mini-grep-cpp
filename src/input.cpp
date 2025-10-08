#include "../include/input.hpp"
#include "../include/debug_logger.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <istream>
#include <memory>
#include <sys/stat.h>
using namespace std;

namespace Input {

InputManager::InputManager() {
  struct stat st;
  fstat(STDIN_FILENO, &st);
  this->is_stdin_piped = !S_ISCHR(st.st_mode);
};
InputManager::~InputManager() = default;

vector<InputObject>
InputManager::get_input_streams(vector<std::filesystem::path> &files) {
  vector<InputObject> res;
  res.reserve(files.size() + 1);
  if (this->is_stdin_piped) {
    DebugLogger::log("Reading from cin \n");
    class StdinStream : public std::istream {
    public:
      StdinStream() : std::istream(std::cin.rdbuf()) {}
      // This will prevent deleting the buffer in destructor
      ~StdinStream() override { rdbuf(nullptr); }
    };

    InputObject inp;
    inp.name = "STDIN";
    inp.type = InputType::STDIN;
    inp.stream = std::make_shared<StdinStream>();

    res.push_back(inp);
    return res;
  };
  if (files.empty())
    return res;

  for (const auto &f : files) {
    DebugLogger::log("Reading from file:", f, "\n");
    auto file = std::make_shared<std::ifstream>(f);
    InputObject inp;
    inp.name = f.filename().string();
    inp.type = InputType::FILE;
    inp.stream = std::move(file);
    res.push_back(inp);
  }

  return res;
};

bool is_stdin_piped;
}; // namespace Input
