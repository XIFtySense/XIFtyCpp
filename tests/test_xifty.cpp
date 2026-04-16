#include "xifty_cpp/xifty.hpp"

#include <cassert>
#include <iostream>

int main() {
  const std::string fixture = std::string(XIFTYCPP_SOURCE_DIR) + "/fixtures/happy.jpg";
  assert(!xifty::version().empty());

  const auto probe = xifty::probe_json(fixture);
  assert(probe.find("\"detected_format\": \"jpeg\"") != std::string::npos);

  const auto normalized =
      xifty::extract_json(fixture, xifty::ViewMode::Normalized);
  assert(normalized.find("\"device.make\"") != std::string::npos);

  std::cout << "xifty cpp tests passed\n";
  return 0;
}
