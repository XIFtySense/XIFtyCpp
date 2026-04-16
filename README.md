# XIFtyCpp

C++ package for XIFty.

This package currently links against the XIFty core repository through the
stable `xifty-ffi` C ABI. Local development expects a sibling checkout of the
core repo at:

- `../XIFty`

You can override that path with `XIFTY_CORE_DIR`.

## Local Development

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
./build/xifty_cpp_example
```

