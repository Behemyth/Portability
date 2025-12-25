# Macros

Include with `#include <portability/macros.h>`.

Macros provide compiler-specific functionality that cannot be expressed in C++ modules (attributes, inline assembly syntax, pragmas).

## Inline Control

| Macro | Description |
|-------|-------------|
| `PORTABILITY_ALWAYS_INLINE` | Force the compiler to inline a function |
| `PORTABILITY_NOINLINE` | Prevent the compiler from inlining a function |
| `PORTABILITY_FLATTEN` | Inline all calls within a function |

```cpp
PORTABILITY_ALWAYS_INLINE int fast_add(int a, int b) {
    return a + b;
}

PORTABILITY_NOINLINE void error_handler() {
    // Keep out of hot path
}
```

## Optimization Hints

| Macro | Description |
|-------|-------------|
| `PORTABILITY_LIKELY(x)` | Hint that condition is likely true |
| `PORTABILITY_UNLIKELY(x)` | Hint that condition is likely false |
| `PORTABILITY_ASSUME(expr)` | Tell compiler to assume expression is true (UB if false) |
| `PORTABILITY_UNREACHABLE()` | Mark code as unreachable (UB if reached) |

```cpp
if (PORTABILITY_UNLIKELY(error)) {
    handle_error();
}

switch (value) {
    case 0: return "zero";
    case 1: return "one";
    default: PORTABILITY_UNREACHABLE();
}
```

## Function Hints

| Macro | Description |
|-------|-------------|
| `PORTABILITY_HOT` | Function is frequently called |
| `PORTABILITY_COLD` | Function is rarely called |
| `PORTABILITY_PURE` | Function has no side effects, may read global memory |
| `PORTABILITY_CONST` | Function result depends only on arguments |

```cpp
PORTABILITY_HOT void process_frame() { }
PORTABILITY_COLD void handle_rare_error() { }

PORTABILITY_PURE int compute(int x);    // May read globals
PORTABILITY_CONST int square(int x);    // Pure function of arguments
```

## Memory & Packing

| Macro | Description |
|-------|-------------|
| `PORTABILITY_RESTRICT` | Pointer does not alias other pointers |
| `PORTABILITY_PACKED_BEGIN` | Begin packed struct region |
| `PORTABILITY_PACKED_END` | End packed struct region |
| `PORTABILITY_PACKED_ATTR` | Apply packed attribute to struct |

```cpp
void process(int* PORTABILITY_RESTRICT a, int* PORTABILITY_RESTRICT b);

PORTABILITY_PACKED_BEGIN
struct PackedData {
    char a;
    int b;
} PORTABILITY_PACKED_ATTR;
PORTABILITY_PACKED_END
```

## Diagnostic Control

| Macro | Description |
|-------|-------------|
| `PORTABILITY_DIAGNOSTIC_PUSH` | Save current warning state |
| `PORTABILITY_DIAGNOSTIC_POP` | Restore previous warning state |
| `PORTABILITY_MSVC_IGNORE(num)` | Disable MSVC warning by number |
| `PORTABILITY_GCC_IGNORE(name)` | Disable GCC warning by name |
| `PORTABILITY_CLANG_IGNORE(name)` | Disable Clang warning by name |

Convenience macros for common warnings:

| Macro | Warnings Disabled |
|-------|-------------------|
| `PORTABILITY_IGNORE_DEPRECATED` | Deprecated declaration warnings |
| `PORTABILITY_IGNORE_UNUSED_PARAMETER` | Unused parameter warnings |
| `PORTABILITY_IGNORE_SHADOW` | Variable shadowing warnings |

```cpp
PORTABILITY_DIAGNOSTIC_PUSH
PORTABILITY_IGNORE_DEPRECATED
use_old_api();  // No warning
PORTABILITY_DIAGNOSTIC_POP
```

## Debugging

| Macro | Description |
|-------|-------------|
| `PORTABILITY_DEBUGBREAK()` | Trigger a debugger breakpoint |

```cpp
if (unexpected_state) {
    PORTABILITY_DEBUGBREAK();
}
```

## Symbol Visibility

| Macro | Description |
|-------|-------------|
| `PORTABILITY_EXPORT` | Export symbol from shared library |
| `PORTABILITY_IMPORT` | Import symbol from shared library |
| `PORTABILITY_HIDDEN` | Hide symbol from shared library |

```cpp
class PORTABILITY_EXPORT PublicApi { };
class PORTABILITY_HIDDEN InternalImpl { };
```

## Optimization Fences

For implementing `DoNotOptimizeAway`-style utilities:

| Macro | Description |
|-------|-------------|
| `PORTABILITY_ASM_FENCE_REGISTER(value)` | Prevent optimization via register constraint |
| `PORTABILITY_ASM_FENCE_MEMORY(value)` | Prevent optimization via memory constraint |
| `PORTABILITY_ASM_CLOBBER_MEMORY()` | Full memory barrier |

Only defined for GCC/Clang. For MSVC, use pragma-disabled sink functions.

## Build Detection

| Macro | Description |
|-------|-------------|
| `PORTABILITY_HAS_ASSERTIONS` | 1 if `NDEBUG` not defined, 0 otherwise |
| `PORTABILITY_HAS_ASAN` | 1 if AddressSanitizer enabled |
| `PORTABILITY_HAS_TSAN` | 1 if ThreadSanitizer enabled |
| `PORTABILITY_HAS_UBSAN` | 1 if UndefinedBehaviorSanitizer enabled |
| `PORTABILITY_HAS_MSAN` | 1 if MemorySanitizer enabled |
| `PORTABILITY_HAS_ANY_SANITIZER` | 1 if any sanitizer enabled |
