# Portability

Cross-platform detection and compiler macros for C++.

```cpp
import synodic.portability;
#include <portability/macros.h>

if constexpr (port::PlatformID == "windows") { }

PORT_ALWAYS_INLINE void fast() { }
```

- [Modules](modules.md)
- [Macros](macros.md)
- [Extensibility](extensibility.md)
