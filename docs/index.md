# Portability

A C++23 library providing cross-platform detection and compiler-specific macros.

## Overview

Portability provides two complementary APIs:

- **Modules** — Compile-time constants for platform/compiler/architecture identity
- **Macros** — Compiler-specific attributes and hints that can't live in modules

## Quick Start

```cpp
import synodic.portability;
#include <portability/macros.h>

// Compile-time platform checks using string IDs
if constexpr (port::PlatformId == "windows") {
    // Windows-specific code
}

// Compiler-specific macros
PORTABILITY_ALWAYS_INLINE void hot_path() {
    // ...
}
```

## Documentation

- [Modules](modules.md) — Platform, compiler, architecture, and build detection
- [Macros](macros.md) — Compiler-specific attributes and hints
- [Extensibility](extensibility.md) — Adding custom platforms, compilers, and architectures