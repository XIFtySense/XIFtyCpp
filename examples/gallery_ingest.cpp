#include "xifty_cpp/xifty.hpp"

#include <iostream>
#include <string>

int main() {
  const std::string fixture = std::string(XIFTYCPP_SOURCE_DIR) + "/fixtures/happy.jpg";
  const auto normalized = xifty::extract_json(fixture, xifty::ViewMode::Normalized);

  std::cout << "{\n"
            << "  \"sourcePath\": \"" << fixture << "\",\n"
            << "  \"format\": \"jpeg\",\n"
            << "  \"normalized\": " << normalized << "\n"
            << "}\n";
  return 0;
}
