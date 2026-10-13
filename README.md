# codemorph

[![CI](https://github.com/PayBridgeOne/codemorph/actions/workflows/ci.yml/badge.svg)](https://github.com/PayBridgeOne/codemorph/actions/workflows/ci.yml)

C++23 encoding utilities for hexadecimal, byte buffers, ASCII, BCD and EBCDIC, including VISA's EBCDIC variant.

## Usage

```cpp
#include <codemorph/codemorph.hpp>

auto packed = codemorph::ascii_to_bcd("1234", codemorph::FieldPadding::NONE);
auto decoded = codemorph::bcd_to_ascii(packed, codemorph::FieldPadding::NONE, 4);
```

```cmake
include(FetchContent)
FetchContent_Declare(
    codemorph
    GIT_REPOSITORY https://github.com/PayBridgeOne/codemorph.git
    GIT_TAG v2.0.0
    GIT_SHALLOW TRUE
)
set(CODEMORPH_ENABLE_TESTING OFF CACHE BOOL "Disable dependency tests")
FetchContent_MakeAvailable(codemorph)
target_link_libraries(your_target PRIVATE codemorph::codemorph)
```

The `v2.0.0` release tag will be created after this change is merged.
Before publication, use the PR commit for evaluation.

## Build and test

CMake 3.20 or newer and a C++23 compiler are required. Standalone tests require an installed Catch2 3 package.
Set `Catch2_DIR` or `CMAKE_PREFIX_PATH` if Catch2 is outside the default search paths.

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build --parallel
ctest --test-dir build --output-on-failure
```

| Option | Default | Purpose |
|--------|---------|---------|
| `CODEMORPH_ENABLE_TESTING` | ON | Build standalone unit tests and benchmark cases |
| `CODEMORPH_ENABLE_WARNINGS` | ON | Enable compiler warnings on library and test targets |
| `CODEMORPH_ENABLE_WARNINGS_AS_ERRORS` | OFF | Treat enabled warnings as errors |

Tests are not built when codemorph is a dependency. If standalone testing is enabled, missing Catch2 is a configuration
error rather than a silently skipped suite.

Existing install rules copy the public header and export `codemorph::codemorph` through `codemorph-config.cmake`,
so `find_package(codemorph CONFIG)` resolves the target. A package version config is deferred.

## Migration and historical notes

See [MIGRATION.md](MIGRATION.md) for the breaking changes from v1.1.1 to v2.0.0.
