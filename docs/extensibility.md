# Extensibility

Override module selection via CMake:

```cmake
set(PORTABILITY_PLATFORM_MODULE "path/to/console.ixx")
set(PORTABILITY_COMPILER_MODULE "path/to/custom.ixx")
set(PORTABILITY_ARCHITECTURE_MODULE "path/to/custom.ixx")
```

Custom modules must export the same interface. Example platform:

```cpp
export module synodic.portability.platform;
import std;

namespace port
{
export inline constexpr std::string_view PlatformID = "console";
export consteval std::string_view PlatformName() noexcept { return "Console"; }
}
```
