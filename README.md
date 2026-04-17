# XIFtyCpp

C++ binding for [XIFty](https://github.com/XIFtySense/XIFty).

`XIFtyCpp` is a light C++ facade over the stable `xifty-ffi` C ABI. It is ready
for source-based use today and is intended to become the canonical C++ package
for XIFty consumers.

## What You Get

- `xifty::version()`
- `xifty::probe_json(path)`
- `xifty::extract_json(path, view)`
- an exception-based C++ layer that stays intentionally thin over the core ABI

## Quickstart

Clone the public core repo as a sibling checkout, then configure and run the
wrapper:

```bash
git clone git@github.com:XIFtySense/XIFty.git ../XIFty
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/xifty_cpp_example
```

If your core checkout lives elsewhere, set `XIFTY_CORE_DIR` before configuring.

For projects using CMake directly, a minimal `FetchContent` setup looks like:

```cmake
include(FetchContent)

FetchContent_Declare(
  XIFtyCpp
  GIT_REPOSITORY https://github.com/XIFtySense/XIFtyCpp.git
  GIT_TAG main
)

FetchContent_MakeAvailable(XIFtyCpp)
target_link_libraries(your_target PRIVATE xifty_cpp)
```

## Status

- source-first and usable today
- built on the stable `xifty-ffi` ABI
- CI validates the wrapper against the public XIFty core repo on every push
- structured for future packaging and binary-distribution work

## Release Model

- source-first today, intended to be consumed from tagged releases
- the public API lives in `include/xifty_cpp/xifty.hpp`
- future binary packaging should build on the same stable `xifty-ffi` seam

## License

MIT
