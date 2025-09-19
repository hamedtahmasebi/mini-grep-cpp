#include "../include/output.hpp"
#include <iostream>

namespace Output {
void ConsoleOutput::write(const std::string &data) { std::cout << data; };
void ConsoleOutput::write_line(const std::string &line) {
  std::cout << line << std::endl;
};
} // namespace Output
