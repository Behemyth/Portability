# Modules

Import with `import synodic.portability;` or import individual modules.

## Platform

**Module:** `synodic.portability.platform`

| Export | Type | Description |
|--------|------|-------------|
| `PlatformId` | `std::string_view` | Unique identifier: `"windows"`, `"linux"`, `"macos"`, or custom |
| `PlatformName()` | `consteval` | Human-readable name: `"Windows"`, `"Linux"`, `"macOS"`, etc. |

```cpp
if constexpr (port::PlatformId == "windows") {
    // Windows-specific code
}
```

## Compiler

**Module:** `synodic.portability.compiler`

| Export | Type | Description |
|--------|------|-------------|
| `CompilerId` | `std::string_view` | Unique identifier: `"msvc"`, `"clang"`, `"gcc"`, or custom |
| `CompilerName()` | `consteval` | Human-readable name: `"MSVC"`, `"Clang"`, `"GCC"`, etc. |
| `CompilerVersion()` | `consteval` | Returns `std::tuple<int, int, int>` (major, minor, patch) |

### Capability Flags

| Export | Description |
|--------|-------------|
| `HasGnuAsm` | GNU inline assembly syntax supported |
| `HasGnuAttributes` | GNU-style attributes (`__attribute__`) supported |
| `HasForceInline` | `__forceinline` supported |
| `HasPragmaOptimize` | `#pragma optimize` supported |

```cpp
if constexpr (port::HasGnuAsm) {
    __asm__ __volatile__("" : : "r"(value));
}
```

## Architecture

**Module:** `synodic.portability.architecture`

| Export | Type | Description |
|--------|------|-------------|
| `ArchitectureId` | `std::string_view` | Unique identifier: `"x64"`, `"x86"`, `"arm64"`, `"arm"`, or custom |
| `ArchitectureName()` | `consteval` | Human-readable name: `"x86-64"`, `"x86"`, `"ARM64"`, `"ARM"`, etc. |
| `PointerSize` | `std::size_t` | Size of pointer in bytes (4 or 8) |

```cpp
static_assert(port::PointerSize == 8, "64-bit required");
```

## Build

**Module:** `synodic.portability.build`

| Export | Type | Description |
|--------|------|-------------|
| `HasAssertions` | `bool` | `true` if `NDEBUG` is not defined |
| `HasAddressSanitizer` | `bool` | ASan enabled |
| `HasThreadSanitizer` | `bool` | TSan enabled |
| `HasUndefinedBehaviorSanitizer` | `bool` | UBSan enabled |
| `HasMemorySanitizer` | `bool` | MSan enabled |
| `HasAnySanitizer` | `bool` | Any sanitizer enabled |

```cpp
if constexpr (port::HasAnySanitizer) {
    // Skip performance-sensitive code path under sanitizers
}
```
