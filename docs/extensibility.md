# Extensibility

Portability supports adding custom platforms, compilers, and architectures without modifying the library itself. This is essential for licensed platforms like game consoles.

## How It Works

CMake selects which module file to compile based on the target. You can override this selection by setting a CMake variable pointing to your custom module.

## Adding a Custom Platform

1. Create your platform module:

```cpp
// playstation5.ixx
export module synodic.portability.platform;

import std;

namespace port
{

export inline constexpr std::string_view PlatformId = "playstation5";

export consteval std::string_view PlatformName() noexcept { return "PlayStation 5"; }

}
```

2. Set the CMake variable before including Portability:

```cmake
set(PORTABILITY_PLATFORM_MODULE "${CMAKE_CURRENT_SOURCE_DIR}/playstation5.ixx")
add_subdirectory(external/portability)
```

## Adding a Custom Compiler

```cpp
// custom_compiler.ixx
export module synodic.portability.compiler;

import std;

namespace port
{

export inline constexpr std::string_view CompilerId = "custom";

export consteval std::string_view CompilerName() noexcept { return "Custom Compiler"; }

export consteval std::tuple<int, int, int> CompilerVersion() noexcept
{
    return {1, 0, 0};
}

// Capability flags - set based on what your compiler supports
export inline constexpr bool HasGnuAsm         = false;
export inline constexpr bool HasGnuAttributes  = false;
export inline constexpr bool HasForceInline    = false;
export inline constexpr bool HasPragmaOptimize = false;

}
```

```cmake
set(PORTABILITY_COMPILER_MODULE "${CMAKE_CURRENT_SOURCE_DIR}/custom_compiler.ixx")
```

## Adding a Custom Architecture

```cpp
// risc_v.ixx
export module synodic.portability.architecture;

import std;

namespace port
{

export inline constexpr std::string_view ArchitectureId = "riscv64";

export consteval std::string_view ArchitectureName() noexcept { return "RISC-V 64"; }

export inline constexpr std::size_t PointerSize = 8;

}
```

```cmake
set(PORTABILITY_ARCHITECTURE_MODULE "${CMAKE_CURRENT_SOURCE_DIR}/risc_v.ixx")
```

## CMake Variables

| Variable | Description |
|----------|-------------|
| `PORTABILITY_PLATFORM_MODULE` | Path to custom platform module |
| `PORTABILITY_COMPILER_MODULE` | Path to custom compiler module |
| `PORTABILITY_ARCHITECTURE_MODULE` | Path to custom architecture module |

## Required Exports

Each custom module must export the same interface as the built-in modules:

### Platform Module

| Export | Type |
|--------|------|
| `PlatformId` | `inline constexpr std::string_view` |
| `PlatformName()` | `consteval std::string_view` |

### Compiler Module

| Export | Type |
|--------|------|
| `CompilerId` | `inline constexpr std::string_view` |
| `CompilerName()` | `consteval std::string_view` |
| `CompilerVersion()` | `consteval std::tuple<int, int, int>` |
| `HasGnuAsm` | `inline constexpr bool` |
| `HasGnuAttributes` | `inline constexpr bool` |
| `HasForceInline` | `inline constexpr bool` |
| `HasPragmaOptimize` | `inline constexpr bool` |

### Architecture Module

| Export | Type |
|--------|------|
| `ArchitectureId` | `inline constexpr std::string_view` |
| `ArchitectureName()` | `consteval std::string_view` |
| `PointerSize` | `inline constexpr std::size_t` |
