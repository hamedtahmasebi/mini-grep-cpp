#pragma once
#include <iostream>
#include <utility>

#ifdef DEBUG
constexpr bool DEBUG_ENABLED = true;
#else
constexpr bool DEBUG_ENABLED = false;
#endif

class DebugLogger {
public:
  template <typename... Args> static void log(Args &&...args) {
    if constexpr (DEBUG_ENABLED) {
      std::cout << "[DEBUG]";
      (std::cout << ... << std::forward<Args>(args)) << std::endl;
    }
  }
};
