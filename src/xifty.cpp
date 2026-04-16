#include "xifty_cpp/xifty.hpp"

extern "C" {
#include "xifty.h"
}

namespace xifty {

namespace {

std::string buffer_to_string(const XiftyBuffer& buffer) {
  if (buffer.ptr == nullptr || buffer.len == 0) {
    return {};
  }
  return std::string(reinterpret_cast<const char*>(buffer.ptr), buffer.len);
}

void free_result(XiftyResult result) {
  xifty_free_buffer(result.output);
  xifty_free_buffer(result.error_message);
}

std::string decode_result(XiftyResult result) {
  const auto status = result.status;
  const auto output = buffer_to_string(result.output);
  const auto error = buffer_to_string(result.error_message);
  free_result(result);

  if (status != XIFTY_STATUS_CODE_SUCCESS) {
    throw Error("xifty ffi error " + std::to_string(status) + ": " + error);
  }

  return output;
}

}  // namespace

std::string version() { return xifty_version(); }

std::string probe_json(const std::string& path) {
  return decode_result(xifty_probe_json(path.c_str()));
}

std::string extract_json(const std::string& path, ViewMode view) {
  return decode_result(
      xifty_extract_json(path.c_str(), static_cast<XiftyViewMode>(view)));
}

}  // namespace xifty

