# Portability

A C++23 library providing cross-platform detection and compiler-specific macros.

## Features

- **C++23 Modules** — Clean `import synodic.portability;` interface
- **String-based Identity** — `if constexpr (port::PlatformId == "windows")` works at compile-time
- **Extensible** — Add custom platforms/compilers without modifying the library
- **Portable Macros** — Compiler-specific attributes with fallbacks

## Usage

```cpp
import synodic.portability;
#include <portability/macros.h>

PORTABILITY_ALWAYS_INLINE void process() {
    if constexpr (port::CompilerId == "msvc") {
        // MSVC-specific optimization
    }
}
```

## Documentation

See [docs/index.md](docs/index.md) for full API reference.