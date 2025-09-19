#pragma once
#include <string>

namespace Output {
enum class OutputMode {
  Normal,
  Count,
};

struct OutputConfig {
  OutputMode mode;
};

class OutputStrategy {
public:
  OutputStrategy(const OutputConfig &config) : config(config) {}
  virtual ~OutputStrategy() = default;
  virtual void write(const std::string &data) = 0;
  virtual void write_line(const std::string &line) = 0;

protected:
  OutputConfig config;
};

class ConsoleOutput : public OutputStrategy {
public:
  using OutputStrategy::OutputStrategy;
  void write(const std::string &data) override;
  void write_line(const std::string &line) override;
};

}; // namespace Output
