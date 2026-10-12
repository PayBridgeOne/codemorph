# Migrating to codemorph v2.0.0

Version 2.0.0 standardizes the library name and introduces source and ABI breaks. There are no compatibility aliases.
Rebuild dependent libraries and applications after updating their includes and calls.

## Naming map

| v1.1.1 | v2.0.0 |
|--------|--------|
| CMake `project(CodeMorph VERSION 1.0.0)` | `project(codemorph VERSION 2.0.0)` |
| `CodeMorph` compatibility target | Removed; link `codemorph::codemorph` |
| `<codemorph.hpp>` | `<codemorph/codemorph.hpp>` |
| Global `CodeMorph` utility class | Free functions in namespace `codemorph` |
| `CodeMorph::<function>` | `codemorph::<function>` |
| `CodeMorph::FieldPadding` | `codemorph::FieldPadding` |
| Generic `ENABLE_TESTING` compatibility option | Use `CODEMORPH_ENABLE_TESTING` |
| Target export file `codemorphConfig.cmake` | `codemorph-config.cmake` |
| Test executable `tests` | `codemorph_tests` |
| Release tag `v1.1.1` | `v2.0.0`, published after merge |

The repository URL is `https://github.com/PayBridgeOne/codemorph.git`.
The folder and FetchContent name remain `codemorph`.
The library target, canonical namespaced target and install namespace remain `codemorph`, `codemorph::codemorph` and
`codemorph::` respectively.

## Source changes

Before:

```cpp
#include <codemorph.hpp>

auto packed = CodeMorph::ascii_to_bcd("1234", CodeMorph::FieldPadding::NONE);
```

After:

```cpp
#include <codemorph/codemorph.hpp>

auto packed = codemorph::ascii_to_bcd("1234", codemorph::FieldPadding::NONE);
```

Function names, overloads, parameters, return types and padding enumerators are preserved.
Lookup tables are now private to the implementation. Encoding bytes, offset advancement, padding and truncation
and existing error behavior are preserved.
This change does not redesign input validation or replace existing exceptions.

## CMake changes

Use `FetchContent_Declare(codemorph ...)` with tag `v2.0.0` after its publication, then link `codemorph::codemorph`.
The raw library target `codemorph` remains; the legacy target `CodeMorph` is removed.

Warning options now apply to the library and standalone tests.
`CODEMORPH_ENABLE_WARNINGS_AS_ERRORS` still defaults to OFF.
If `CODEMORPH_ENABLE_TESTING` is ON for a standalone build, Catch2 3 is required; configuration no longer silently skips
tests when it is missing. Dependency builds continue to omit standalone tests.

Existing installation names and the header destination have changed. Full installed-package support, package config
generation and version config generation remain deferred. No existing release tag is moved or replaced.

isocraft must update its codemorph includes, calls and publicly exposed `FieldPadding` types. The corresponding isocraft
release is v3.0.0. canonical-switch will consume both new releases after publication.
