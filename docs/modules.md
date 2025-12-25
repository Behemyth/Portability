# Modules

```cpp
import synodic.portability;
```

## Platform

`port::PlatformID` — `"windows"`, `"linux"`, `"macos"`  
`port::PlatformName()` — `"Windows"`, `"Linux"`, `"macOS"`

## Compiler

`port::CompilerID` — `"msvc"`, `"clang"`, `"gcc"`  
`port::CompilerName()` — `"MSVC"`, `"Clang"`, `"GCC"`  
`port::CompilerVersion()` — `std::tuple<int, int, int>`

Capabilities: `HasGnuAsm`, `HasGnuAttributes`, `HasForceInline`, `HasPragmaOptimize`

## Architecture

`port::ArchitectureID` — `"x64"`, `"x86"`, `"arm64"`, `"arm"`  
`port::ArchitectureName()` — `"x86-64"`, `"x86"`, `"ARM64"`, `"ARM"`  
`port::PointerSize` — `4` or `8`

## Build

`port::HasAssertions`, `port::HasAddressSanitizer`, `port::HasThreadSanitizer`, `port::HasUndefinedBehaviorSanitizer`, `port::HasMemorySanitizer`, `port::HasAnySanitizer`
