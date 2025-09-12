#pragma once

#include <istream>
#include <memory>
#include <string>
#include <vector>
namespace Input {
class InputManager {
public:
  InputManager();
  ~InputManager();

  std::vector<std::unique_ptr<std::istream>>
  get_input_streams(std::vector<std::string> *files);

private:
  bool is_stdin_piped;
};
} // namespace Input
