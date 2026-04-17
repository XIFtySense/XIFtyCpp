#include "xifty_cpp/xifty.hpp"

#include <cassert>
#include <iostream>
#include <string>

namespace {

std::string fixture() {
  return std::string(XIFTYCPP_SOURCE_DIR) + "/fixtures/happy.jpg";
}

void expect_contains(const std::string& haystack, const std::string& needle) {
  assert(haystack.find(needle) != std::string::npos);
}

}  // namespace

int main() {
  const auto path = fixture();

  assert(!xifty::version().empty());

  const auto probe = xifty::probe_json(path);
  expect_contains(probe, "\"schema_version\": \"0.1.0\"");
  expect_contains(probe, "\"detected_format\": \"jpeg\"");
  expect_contains(probe, "\"container\": \"jpeg\"");

  const auto full = xifty::extract_json(path, xifty::ViewMode::Full);
  expect_contains(full, "\"raw\"");
  expect_contains(full, "\"interpreted\"");
  expect_contains(full, "\"normalized\"");
  expect_contains(full, "\"report\"");

  const auto raw = xifty::extract_json(path, xifty::ViewMode::Raw);
  expect_contains(raw, "\"ImageWidth\"");
  expect_contains(raw, "\"APP1\"");

  const auto interpreted = xifty::extract_json(path, xifty::ViewMode::Interpreted);
  expect_contains(interpreted, "\"Make\"");
  expect_contains(interpreted, "\"Model\"");
  expect_contains(interpreted, "\"DateTimeOriginal\"");

  const auto normalized =
      xifty::extract_json(path, xifty::ViewMode::Normalized);
  expect_contains(normalized, "\"device.make\"");
  expect_contains(normalized, "\"XIFtyCam\"");
  expect_contains(normalized, "\"captured_at\"");
  expect_contains(normalized, "\"2024-04-16T12:34:56\"");

  const auto report = xifty::extract_json(path, xifty::ViewMode::Report);
  expect_contains(report, "\"issues\": []");
  expect_contains(report, "\"conflicts\": []");

  std::cout << "xifty cpp tests passed\n";
  return 0;
}
