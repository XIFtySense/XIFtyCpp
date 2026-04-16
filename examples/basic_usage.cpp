#include "xifty_cpp/xifty.hpp"

#include <iostream>

int main() {
  const std::string fixture = std::string(XIFTYCPP_SOURCE_DIR) + "/fixtures/happy.jpg";
  std::cout << "XIFty version: " << xifty::version() << "\n";
  std::cout << xifty::extract_json(fixture, xifty::ViewMode::Normalized)
            << "\n";
  return 0;
}
