#pragma once

#include <filesystem>
#include <istream>
#include <memory>
#include <vector>
namespace Input {

enum class InputType { FILE, STDIN };

struct InputObject {
  std::string name;
  InputType type;
  std::shared_ptr<std::istream> stream;
};

class InputManager {
public:
  InputManager();
  ~InputManager();

  std::vector<InputObject>
  get_input_streams(std::vector<std::filesystem::path> &files);

private:
  bool is_stdin_piped;
};
} // namespace Input
