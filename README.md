# Portability

A C++ library providing cross-platform detection, macros, and interfaces.

## Features

- **TODO**

## Usage

```cpp
import synodic.portability;
#include <portability/macros.h>

PORT_ALWAYS_INLINE void process() {
    if constexpr (port::CompilerId == "msvc") {
        // MSVC-specific optimization
    }
}
```

## Documentation

See [docs/index.md](docs/index.md) for full API reference.