#pragma once

#include <stdexcept>
#include <string>

namespace xifty {

enum class ViewMode {
  Full = 0,
  Raw = 1,
  Interpreted = 2,
  Normalized = 3,
  Report = 4,
};

class Error : public std::runtime_error {
 public:
  explicit Error(const std::string& message)
      : std::runtime_error(message) {}
};

std::string version();
std::string probe_json(const std::string& path);
std::string extract_json(const std::string& path, ViewMode view = ViewMode::Full);

}  // namespace xifty

