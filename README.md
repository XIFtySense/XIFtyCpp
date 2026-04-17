# XIFty for C++

`XIFtyCpp` is the official C++ binding repo for XIFty.

It provides a thin C++ facade over the stable `xifty-ffi` ABI so C++ programs
can probe files and extract metadata views without binding directly to the raw C
layer.

## What It Does

XIFty exposes four complementary metadata views:

- `raw`
- `interpreted`
- `normalized`
- `report`

This binding keeps that contract intact and adds a small exception-based C++
surface.

## Quick Example

```cpp
const auto normalized = xifty::extract_json("photo.jpg", xifty::ViewMode::Normalized);
std::cout << normalized << "\n";
```

## API

- `xifty::version()`
- `xifty::probe_json(path)`
- `xifty::extract_json(path, view)`

## Why Use It

Use this binding when you want:

- native C++ access to XIFty
- stable normalized metadata for application logic
- raw and interpreted metadata when provenance matters
- a minimal C++ facade over the stable ABI

## Local Setup

This repo no longer assumes a sibling `../XIFty` checkout. By default, CMake
uses a repo-local `.xifty-core` cache and refreshes it during configure.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/xifty_cpp_example
./build/xifty_cpp_gallery_example
```

You can still override the core location explicitly with `XIFTY_CORE_DIR`.

## Status

- source-first and usable today
- built on the stable `xifty-ffi` ABI
- CI validates the wrapper against the public XIFty core repo

## License

MIT
