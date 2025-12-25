#pragma once

// ============================================================================
// Inline Control
// ============================================================================

#if defined(_MSC_VER)
	#define PORTABILITY_ALWAYS_INLINE __forceinline
#elif defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_ALWAYS_INLINE [[gnu::always_inline]] inline
#else
	#define PORTABILITY_ALWAYS_INLINE inline
#endif

#if defined(_MSC_VER)
	#define PORTABILITY_NOINLINE __declspec(noinline)
#elif defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_NOINLINE [[gnu::noinline]]
#else
	#define PORTABILITY_NOINLINE
#endif

#if defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_FLATTEN [[gnu::flatten]]
#elif defined(_MSC_VER) && _MSC_VER >= 1935
	#define PORTABILITY_FLATTEN [[msvc::forceinline_calls]]
#else
	#define PORTABILITY_FLATTEN
#endif

// ============================================================================
// Optimization Hints
// ============================================================================

#if defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_LIKELY(x)   __builtin_expect(!!(x), 1)
	#define PORTABILITY_UNLIKELY(x) __builtin_expect(!!(x), 0)
#else
	#define PORTABILITY_LIKELY(x)   (x)
	#define PORTABILITY_UNLIKELY(x) (x)
#endif

#if defined(_MSC_VER)
	#define PORTABILITY_ASSUME(expr) __assume(expr)
#elif defined(__clang__)
	#define PORTABILITY_ASSUME(expr) __builtin_assume(expr)
#elif defined(__GNUC__) && __GNUC__ >= 13
	#define PORTABILITY_ASSUME(expr) __attribute__((assume(expr)))
#else
	#define PORTABILITY_ASSUME(expr) ((void)0)
#endif

#if defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
	#define PORTABILITY_UNREACHABLE() __assume(0)
#else
	#define PORTABILITY_UNREACHABLE() ((void)0)
#endif

// ============================================================================
// Function Temperature Hints
// ============================================================================

#if defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_COLD [[gnu::cold]]
	#define PORTABILITY_HOT  [[gnu::hot]]
#else
	#define PORTABILITY_COLD
	#define PORTABILITY_HOT
#endif

// ============================================================================
// Function Purity Hints
// ============================================================================

#if defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_PURE  [[gnu::pure]]
	#define PORTABILITY_CONST [[gnu::const]]
#else
	#define PORTABILITY_PURE
	#define PORTABILITY_CONST
#endif

// ============================================================================
// Pointer Aliasing
// ============================================================================

#if defined(_MSC_VER)
	#define PORTABILITY_RESTRICT __restrict
#elif defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_RESTRICT __restrict__
#else
	#define PORTABILITY_RESTRICT
#endif

// ============================================================================
// Struct Packing
// ============================================================================

#if defined(_MSC_VER)
	#define PORTABILITY_PACKED_BEGIN __pragma(pack(push, 1))
	#define PORTABILITY_PACKED_END   __pragma(pack(pop))
	#define PORTABILITY_PACKED_ATTR
#elif defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_PACKED_BEGIN
	#define PORTABILITY_PACKED_END
	#define PORTABILITY_PACKED_ATTR __attribute__((packed))
#else
	#define PORTABILITY_PACKED_BEGIN
	#define PORTABILITY_PACKED_END
	#define PORTABILITY_PACKED_ATTR
#endif

// ============================================================================
// Diagnostic Control
// ============================================================================

#if defined(_MSC_VER)
	#define PORTABILITY_DIAGNOSTIC_PUSH __pragma(warning(push))
	#define PORTABILITY_DIAGNOSTIC_POP  __pragma(warning(pop))
#elif defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
	#define PORTABILITY_DIAGNOSTIC_POP  _Pragma("GCC diagnostic pop")
#else
	#define PORTABILITY_DIAGNOSTIC_PUSH
	#define PORTABILITY_DIAGNOSTIC_POP
#endif

#define PORTABILITY_PRAGMA_IMPL(x) _Pragma(#x)
#define PORTABILITY_PRAGMA(x)      PORTABILITY_PRAGMA_IMPL(x)

#if defined(_MSC_VER)
	#define PORTABILITY_MSVC_IGNORE(num)   __pragma(warning(disable : num))
	#define PORTABILITY_GCC_IGNORE(name)
	#define PORTABILITY_CLANG_IGNORE(name)
#elif defined(__clang__)
	#define PORTABILITY_MSVC_IGNORE(num)
	#define PORTABILITY_GCC_IGNORE(name)
	#define PORTABILITY_CLANG_IGNORE(name) PORTABILITY_PRAGMA(clang diagnostic ignored name)
#elif defined(__GNUC__)
	#define PORTABILITY_MSVC_IGNORE(num)
	#define PORTABILITY_GCC_IGNORE(name)   PORTABILITY_PRAGMA(GCC diagnostic ignored name)
	#define PORTABILITY_CLANG_IGNORE(name)
#else
	#define PORTABILITY_MSVC_IGNORE(num)
	#define PORTABILITY_GCC_IGNORE(name)
	#define PORTABILITY_CLANG_IGNORE(name)
#endif

#define PORTABILITY_IGNORE_DEPRECATED       \
	PORTABILITY_MSVC_IGNORE(4996)           \
	PORTABILITY_GCC_IGNORE("-Wdeprecated-declarations") \
	PORTABILITY_CLANG_IGNORE("-Wdeprecated-declarations")

#define PORTABILITY_IGNORE_UNUSED_PARAMETER \
	PORTABILITY_MSVC_IGNORE(4100)           \
	PORTABILITY_GCC_IGNORE("-Wunused-parameter") \
	PORTABILITY_CLANG_IGNORE("-Wunused-parameter")

#define PORTABILITY_IGNORE_SHADOW           \
	PORTABILITY_MSVC_IGNORE(4456)           \
	PORTABILITY_MSVC_IGNORE(4457)           \
	PORTABILITY_GCC_IGNORE("-Wshadow")      \
	PORTABILITY_CLANG_IGNORE("-Wshadow")

// ============================================================================
// Optimization Fence (for DoNotOptimizeAway implementations)
// ============================================================================

#if defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_ASM_FENCE_REGISTER(value) __asm__ __volatile__("" : : "r"(value))
	#define PORTABILITY_ASM_FENCE_MEMORY(value)   __asm__ __volatile__("" : : "m"(value) : "memory")
	#define PORTABILITY_ASM_CLOBBER_MEMORY()      __asm__ __volatile__("" : : : "memory")
#else
	#define PORTABILITY_ASM_FENCE_REGISTER(value)
	#define PORTABILITY_ASM_FENCE_MEMORY(value)
	#define PORTABILITY_ASM_CLOBBER_MEMORY()
#endif

// ============================================================================
// Debugger
// ============================================================================

#if defined(_MSC_VER)
	#define PORTABILITY_DEBUGBREAK() __debugbreak()
#elif defined(__clang__)
	#define PORTABILITY_DEBUGBREAK() __builtin_debugtrap()
#elif defined(__GNUC__) && (defined(__i386__) || defined(__x86_64__))
	#define PORTABILITY_DEBUGBREAK() __asm__ __volatile__("int3")
#elif defined(__GNUC__)
	#define PORTABILITY_DEBUGBREAK() __builtin_trap()
#else
	#include <csignal>
	#define PORTABILITY_DEBUGBREAK() std::raise(SIGTRAP)
#endif

// ============================================================================
// Symbol Visibility
// ============================================================================

#if defined(_WIN32)
	#define PORTABILITY_EXPORT __declspec(dllexport)
	#define PORTABILITY_IMPORT __declspec(dllimport)
	#define PORTABILITY_HIDDEN
#elif defined(__clang__) || defined(__GNUC__)
	#define PORTABILITY_EXPORT __attribute__((visibility("default")))
	#define PORTABILITY_IMPORT __attribute__((visibility("default")))
	#define PORTABILITY_HIDDEN __attribute__((visibility("hidden")))
#else
	#define PORTABILITY_EXPORT
	#define PORTABILITY_IMPORT
	#define PORTABILITY_HIDDEN
#endif

// ============================================================================
// Assertions
// ============================================================================

#if defined(NDEBUG)
	#define PORTABILITY_HAS_ASSERTIONS 0
#else
	#define PORTABILITY_HAS_ASSERTIONS 1
#endif

// ============================================================================
// Sanitizer Detection
// ============================================================================

#if defined(__SANITIZE_ADDRESS__)
	#define PORTABILITY_HAS_ASAN 1
#elif defined(__has_feature)
	#if __has_feature(address_sanitizer)
		#define PORTABILITY_HAS_ASAN 1
	#else
		#define PORTABILITY_HAS_ASAN 0
	#endif
#else
	#define PORTABILITY_HAS_ASAN 0
#endif

#if defined(__SANITIZE_THREAD__)
	#define PORTABILITY_HAS_TSAN 1
#elif defined(__has_feature)
	#if __has_feature(thread_sanitizer)
		#define PORTABILITY_HAS_TSAN 1
	#else
		#define PORTABILITY_HAS_TSAN 0
	#endif
#else
	#define PORTABILITY_HAS_TSAN 0
#endif

#if defined(__has_feature)
	#if __has_feature(undefined_behavior_sanitizer)
		#define PORTABILITY_HAS_UBSAN 1
	#else
		#define PORTABILITY_HAS_UBSAN 0
	#endif
#else
	#define PORTABILITY_HAS_UBSAN 0
#endif

#if defined(__has_feature)
	#if __has_feature(memory_sanitizer)
		#define PORTABILITY_HAS_MSAN 1
	#else
		#define PORTABILITY_HAS_MSAN 0
	#endif
#else
	#define PORTABILITY_HAS_MSAN 0
#endif

#define PORTABILITY_HAS_ANY_SANITIZER \
	(PORTABILITY_HAS_ASAN || PORTABILITY_HAS_TSAN || PORTABILITY_HAS_UBSAN || PORTABILITY_HAS_MSAN)
