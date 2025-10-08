#pragma once
#include <iostream>
#include <source_location>
#include <string_view>

class DebugLogger {
public:
  static inline bool enabled = false;

  template <typename T>
  static void
  log(const T &message,
      const std::source_location &location = std::source_location::current()) {
        
  }
};
