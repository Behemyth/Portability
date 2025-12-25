// SPDX-License-Identifier: MIT
// Portability Library - Cross-platform compiler macros
// This header provides macros for compiler-specific features that cannot be exported from C++20 modules.

#ifndef SYNODIC_PORTABILITY_MACROS_H
#define SYNODIC_PORTABILITY_MACROS_H

// ============================================================================
// Compiler Detection
// ============================================================================

#if defined(__clang__)
	#define PORTABILITY_COMPILER_CLANG 1
	#define PORTABILITY_COMPILER_GCC   0
	#define PORTABILITY_COMPILER_MSVC  0
#elif defined(__GNUC__)
	#define PORTABILITY_COMPILER_CLANG 0
	#define PORTABILITY_COMPILER_GCC   1
	#define PORTABILITY_COMPILER_MSVC  0
#elif defined(_MSC_VER)
	#define PORTABILITY_COMPILER_CLANG 0
	#define PORTABILITY_COMPILER_GCC   0
	#define PORTABILITY_COMPILER_MSVC  1
#else
	#define PORTABILITY_COMPILER_CLANG 0
	#define PORTABILITY_COMPILER_GCC   0
	#define PORTABILITY_COMPILER_MSVC  0
#endif

// ============================================================================
// Inline Control
// ============================================================================

/// Forces the compiler to inline a function
#if PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_ALWAYS_INLINE __forceinline
#elif PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_ALWAYS_INLINE [[gnu::always_inline]] inline
#else
	#define PORTABILITY_ALWAYS_INLINE inline
#endif

/// Prevents the compiler from inlining a function
#if PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_NOINLINE __declspec(noinline)
#elif PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_NOINLINE [[gnu::noinline]]
#else
	#define PORTABILITY_NOINLINE
#endif

/// Inlines all calls within a function (aggressive inlining)
#if PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_FLATTEN [[gnu::flatten]]
#elif PORTABILITY_COMPILER_MSVC && _MSC_VER >= 1935
	#define PORTABILITY_FLATTEN [[msvc::forceinline_calls]]
#else
	#define PORTABILITY_FLATTEN
#endif

// ============================================================================
// Optimization Hints
// ============================================================================

/// Branch prediction hints for conditions (legacy style)
/// Prefer [[likely]]/[[unlikely]] on statements in C++20+
#if PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_LIKELY(x)   __builtin_expect(!!(x), 1)
	#define PORTABILITY_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
	#define PORTABILITY_LIKELY(x)   (x)
	#define PORTABILITY_UNLIKELY(x) (x)
#endif

/// Tells the compiler to assume a condition is true (UB if false at runtime)
#if PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_ASSUME(expr) __assume(expr)
#elif PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_ASSUME(expr) __builtin_assume(expr)
#elif PORTABILITY_COMPILER_GCC && __GNUC__ >= 13
	#define PORTABILITY_ASSUME(expr) __attribute__((assume(expr)))
#else
	#define PORTABILITY_ASSUME(expr) ((void)0)
#endif

/// Marks code as unreachable (UB if reached)
#if PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_UNREACHABLE() __builtin_unreachable()
#elif PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_UNREACHABLE() __assume(0)
#else
	#define PORTABILITY_UNREACHABLE() ((void)0)
#endif

// ============================================================================
// Function Temperature Hints
// ============================================================================

/// Hint that a function is rarely called (cold path)
#if PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_COLD [[gnu::cold]]
#else
	#define PORTABILITY_COLD
#endif

/// Hint that a function is frequently called (hot path)
#if PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_HOT [[gnu::hot]]
#else
	#define PORTABILITY_HOT
#endif

// ============================================================================
// Function Purity Hints
// ============================================================================

/// Function has no side effects, may read global memory
#if PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_PURE [[gnu::pure]]
#else
	#define PORTABILITY_PURE
#endif

/// Function result depends only on arguments, no memory reads
#if PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_CONST [[gnu::const]]
#else
	#define PORTABILITY_CONST
#endif

// ============================================================================
// Symbol Visibility (Shared Libraries / DLLs)
// ============================================================================

#if defined(_WIN32) || defined(_WIN64)
	#define PORTABILITY_EXPORT __declspec(dllexport)
	#define PORTABILITY_IMPORT __declspec(dllimport)
	#define PORTABILITY_HIDDEN
#elif PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_EXPORT __attribute__((visibility("default")))
	#define PORTABILITY_IMPORT __attribute__((visibility("default")))
	#define PORTABILITY_HIDDEN __attribute__((visibility("hidden")))
#else
	#define PORTABILITY_EXPORT
	#define PORTABILITY_IMPORT
	#define PORTABILITY_HIDDEN
#endif

// ============================================================================
// Pointer Aliasing
// ============================================================================

/// Hint that a pointer does not alias other pointers
#if PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_RESTRICT __restrict
#elif PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_RESTRICT __restrict__
#else
	#define PORTABILITY_RESTRICT
#endif

// ============================================================================
// Struct Packing
// ============================================================================

#if PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_PACKED_BEGIN __pragma(pack(push, 1))
	#define PORTABILITY_PACKED_END   __pragma(pack(pop))
	#define PORTABILITY_PACKED_ATTR
#elif PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_PACKED_BEGIN
	#define PORTABILITY_PACKED_END
	#define PORTABILITY_PACKED_ATTR __attribute__((packed))
#else
	#define PORTABILITY_PACKED_BEGIN
	#define PORTABILITY_PACKED_END
	#define PORTABILITY_PACKED_ATTR
#endif

// ============================================================================
// Debugger
// ============================================================================

/// Trigger a debugger breakpoint
#if PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_DEBUGBREAK() __debugbreak()
#elif PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_DEBUGBREAK() __builtin_debugtrap()
#elif PORTABILITY_COMPILER_GCC && (defined(__i386__) || defined(__x86_64__))
	#define PORTABILITY_DEBUGBREAK() __asm__ __volatile__("int3")
#elif PORTABILITY_COMPILER_GCC
	#define PORTABILITY_DEBUGBREAK() __builtin_trap()
#else
	#include <csignal>
	#define PORTABILITY_DEBUGBREAK() std::raise(SIGTRAP)
#endif

// ============================================================================
// Diagnostic Control
// ============================================================================

#if PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_DIAGNOSTIC_PUSH __pragma(warning(push))
	#define PORTABILITY_DIAGNOSTIC_POP  __pragma(warning(pop))
#elif PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
	#define PORTABILITY_DIAGNOSTIC_POP  _Pragma("GCC diagnostic pop")
#else
	#define PORTABILITY_DIAGNOSTIC_PUSH
	#define PORTABILITY_DIAGNOSTIC_POP
#endif

// Helper for pragma stringification
#define PORTABILITY_PRAGMA_IMPL(x) _Pragma(#x)
#define PORTABILITY_PRAGMA(x)      PORTABILITY_PRAGMA_IMPL(x)

#if PORTABILITY_COMPILER_MSVC
	#define PORTABILITY_MSVC_IGNORE(num)  __pragma(warning(disable : num))
	#define PORTABILITY_GCC_IGNORE(name)
	#define PORTABILITY_CLANG_IGNORE(name)
#elif PORTABILITY_COMPILER_CLANG
	#define PORTABILITY_MSVC_IGNORE(num)
	#define PORTABILITY_GCC_IGNORE(name)
	#define PORTABILITY_CLANG_IGNORE(name) PORTABILITY_PRAGMA(clang diagnostic ignored name)
#elif PORTABILITY_COMPILER_GCC
	#define PORTABILITY_MSVC_IGNORE(num)
	#define PORTABILITY_GCC_IGNORE(name) PORTABILITY_PRAGMA(GCC diagnostic ignored name)
	#define PORTABILITY_CLANG_IGNORE(name)
#else
	#define PORTABILITY_MSVC_IGNORE(num)
	#define PORTABILITY_GCC_IGNORE(name)
	#define PORTABILITY_CLANG_IGNORE(name)
#endif

// Common warning suppressions
#define PORTABILITY_IGNORE_DEPRECATED                       \
	PORTABILITY_MSVC_IGNORE(4996)                           \
	PORTABILITY_GCC_IGNORE("-Wdeprecated-declarations")     \
	PORTABILITY_CLANG_IGNORE("-Wdeprecated-declarations")

#define PORTABILITY_IGNORE_UNUSED_PARAMETER                 \
	PORTABILITY_MSVC_IGNORE(4100)                           \
	PORTABILITY_GCC_IGNORE("-Wunused-parameter")            \
	PORTABILITY_CLANG_IGNORE("-Wunused-parameter")

#define PORTABILITY_IGNORE_SHADOW                           \
	PORTABILITY_MSVC_IGNORE(4456)                           \
	PORTABILITY_MSVC_IGNORE(4457)                           \
	PORTABILITY_GCC_IGNORE("-Wshadow")                      \
	PORTABILITY_CLANG_IGNORE("-Wshadow")

// ============================================================================
// Optimization Fence (for DoNotOptimizeAway implementations)
// ============================================================================

/// Inline assembly memory barrier - use for implementing DoNotOptimizeAway
/// Only available on compilers supporting GNU asm syntax
#if PORTABILITY_COMPILER_GCC || PORTABILITY_COMPILER_CLANG
	/// Prevents compiler from optimizing away a value (register constraint)
	#define PORTABILITY_ASM_FENCE_REGISTER(value) __asm__ __volatile__("" : : "r"(value))
	/// Prevents compiler from optimizing away a value (memory constraint with barrier)
	#define PORTABILITY_ASM_FENCE_MEMORY(value)   __asm__ __volatile__("" : : "m"(value) : "memory")
	/// Full memory barrier
	#define PORTABILITY_ASM_CLOBBER_MEMORY()      __asm__ __volatile__("" : : : "memory")
#endif

/// For MSVC: Use pragma-disabled sink function pattern
/// Downstream libraries should implement:
/// #if PORTABILITY_COMPILER_MSVC
///     #pragma optimize("", off)
///     inline void CompilerMustNotElideSink(void const*) noexcept {}
///     #pragma optimize("", on)
/// #endif

#endif // SYNODIC_PORTABILITY_MACROS_H
