#pragma once

// ============================================================================
// Inline Control
// ============================================================================

#if defined(_MSC_VER)
	#define PORT_ALWAYS_INLINE __forceinline
#elif defined(__clang__) || defined(__GNUC__)
	#define PORT_ALWAYS_INLINE [[gnu::always_inline]] inline
#else
	#define PORT_ALWAYS_INLINE inline
#endif

#if defined(_MSC_VER)
	#define PORT_NOINLINE __declspec(noinline)
#elif defined(__clang__) || defined(__GNUC__)
	#define PORT_NOINLINE [[gnu::noinline]]
#else
	#define PORT_NOINLINE
#endif

#if defined(__clang__) || defined(__GNUC__)
	#define PORT_FLATTEN [[gnu::flatten]]
#elif defined(_MSC_VER) && _MSC_VER >= 1935
	#define PORT_FLATTEN [[msvc::forceinline_calls]]
#else
	#define PORT_FLATTEN
#endif

// ============================================================================
// Optimization Hints
// ============================================================================

#if defined(_MSC_VER)
	#define PORT_ASSUME(expr) __assume(expr)
#elif defined(__clang__)
	#define PORT_ASSUME(expr) __builtin_assume(expr)
#elif defined(__GNUC__) && __GNUC__ >= 13
	#define PORT_ASSUME(expr) __attribute__((assume(expr)))
#else
	#define PORT_ASSUME(expr) ((void)0)
#endif

#if defined(__clang__) || defined(__GNUC__)
	#define PORT_UNREACHABLE() __builtin_unreachable()
#elif defined(_MSC_VER)
	#define PORT_UNREACHABLE() __assume(0)
#else
	#define PORT_UNREACHABLE() ((void)0)
#endif

// ============================================================================
// Function Temperature Hints
// ============================================================================

#if defined(__clang__) || defined(__GNUC__)
	#define PORT_COLD [[gnu::cold]]
	#define PORT_HOT  [[gnu::hot]]
#else
	#define PORT_COLD
	#define PORT_HOT
#endif

// ============================================================================
// Function Purity Hints
// ============================================================================

#if defined(__clang__) || defined(__GNUC__)
	#define PORT_PURE  [[gnu::pure]]
	#define PORT_CONST [[gnu::const]]
#else
	#define PORT_PURE
	#define PORT_CONST
#endif

// ============================================================================
// Pointer Aliasing
// ============================================================================

#if defined(_MSC_VER)
	#define PORT_RESTRICT __restrict
#elif defined(__clang__) || defined(__GNUC__)
	#define PORT_RESTRICT __restrict__
#else
	#define PORT_RESTRICT
#endif

// ============================================================================
// Struct Packing
// ============================================================================

#if defined(_MSC_VER)
	#define PORT_PACKED_BEGIN __pragma(pack(push, 1))
	#define PORT_PACKED_END   __pragma(pack(pop))
	#define PORT_PACKED_ATTR
#elif defined(__clang__) || defined(__GNUC__)
	#define PORT_PACKED_BEGIN
	#define PORT_PACKED_END
	#define PORT_PACKED_ATTR __attribute__((packed))
#else
	#define PORT_PACKED_BEGIN
	#define PORT_PACKED_END
	#define PORT_PACKED_ATTR
#endif

// ============================================================================
// Diagnostic Control
// ============================================================================

#if defined(_MSC_VER)
	#define PORT_DIAGNOSTIC_PUSH __pragma(warning(push))
	#define PORT_DIAGNOSTIC_POP  __pragma(warning(pop))
#elif defined(__clang__) || defined(__GNUC__)
	#define PORT_DIAGNOSTIC_PUSH _Pragma("GCC diagnostic push")
	#define PORT_DIAGNOSTIC_POP  _Pragma("GCC diagnostic pop")
#else
	#define PORT_DIAGNOSTIC_PUSH
	#define PORT_DIAGNOSTIC_POP
#endif

#define PORT_PRAGMA_IMPL(x) _Pragma(#x)
#define PORT_PRAGMA(x)      PORT_PRAGMA_IMPL(x)

#if defined(_MSC_VER)
	#define PORT_MSVC_IGNORE(num)  __pragma(warning(disable : num))
	#define PORT_GCC_IGNORE(name)
	#define PORT_CLANG_IGNORE(name)
#elif defined(__clang__)
	#define PORT_MSVC_IGNORE(num)
	#define PORT_GCC_IGNORE(name)
	#define PORT_CLANG_IGNORE(name) PORT_PRAGMA(clang diagnostic ignored name)
#elif defined(__GNUC__)
	#define PORT_MSVC_IGNORE(num)
	#define PORT_GCC_IGNORE(name)  PORT_PRAGMA(GCC diagnostic ignored name)
	#define PORT_CLANG_IGNORE(name)
#else
	#define PORT_MSVC_IGNORE(num)
	#define PORT_GCC_IGNORE(name)
	#define PORT_CLANG_IGNORE(name)
#endif

#define PORT_IGNORE_DEPRECATED       \
	PORT_MSVC_IGNORE(4996)           \
	PORT_GCC_IGNORE("-Wdeprecated-declarations") \
	PORT_CLANG_IGNORE("-Wdeprecated-declarations")

#define PORT_IGNORE_UNUSED_PARAMETER \
	PORT_MSVC_IGNORE(4100)           \
	PORT_GCC_IGNORE("-Wunused-parameter") \
	PORT_CLANG_IGNORE("-Wunused-parameter")

#define PORT_IGNORE_SHADOW           \
	PORT_MSVC_IGNORE(4456)           \
	PORT_MSVC_IGNORE(4457)           \
	PORT_GCC_IGNORE("-Wshadow")      \
	PORT_CLANG_IGNORE("-Wshadow")

// ============================================================================
// Optimization Fence (for DoNotOptimizeAway implementations)
// ============================================================================

#if defined(__clang__) || defined(__GNUC__)
	#define PORT_ASM_FENCE_REGISTER(value) __asm__ __volatile__("" : : "r"(value))
	#define PORT_ASM_FENCE_MEMORY(value)   __asm__ __volatile__("" : : "m"(value) : "memory")
	#define PORT_ASM_CLOBBER_MEMORY()      __asm__ __volatile__("" : : : "memory")
#else
	#define PORT_ASM_FENCE_REGISTER(value)
	#define PORT_ASM_FENCE_MEMORY(value)
	#define PORT_ASM_CLOBBER_MEMORY()
#endif

// ============================================================================
// Symbol Visibility
// ============================================================================

#if defined(_WIN32)
	#define PORT_EXPORT __declspec(dllexport)
	#define PORT_IMPORT __declspec(dllimport)
	#define PORT_HIDDEN
#elif defined(__clang__) || defined(__GNUC__)
	#define PORT_EXPORT __attribute__((visibility("default")))
	#define PORT_IMPORT __attribute__((visibility("default")))
	#define PORT_HIDDEN __attribute__((visibility("hidden")))
#else
	#define PORT_EXPORT
	#define PORT_IMPORT
	#define PORT_HIDDEN
#endif

// ============================================================================
// Assertions
// ============================================================================

#if defined(NDEBUG)
	#define PORT_HAS_ASSERTIONS 0
#else
	#define PORT_HAS_ASSERTIONS 1
#endif

// ============================================================================
// Sanitizer Detection
// ============================================================================

#if defined(__SANITIZE_ADDRESS__)
	#define PORT_HAS_ASAN 1
#elif defined(__has_feature)
	#if __has_feature(address_sanitizer)
		#define PORT_HAS_ASAN 1
	#else
		#define PORT_HAS_ASAN 0
	#endif
#else
	#define PORT_HAS_ASAN 0
#endif

#if defined(__SANITIZE_THREAD__)
	#define PORT_HAS_TSAN 1
#elif defined(__has_feature)
	#if __has_feature(thread_sanitizer)
		#define PORT_HAS_TSAN 1
	#else
		#define PORT_HAS_TSAN 0
	#endif
#else
	#define PORT_HAS_TSAN 0
#endif

#if defined(__has_feature)
	#if __has_feature(undefined_behavior_sanitizer)
		#define PORT_HAS_UBSAN 1
	#else
		#define PORT_HAS_UBSAN 0
	#endif
#else
	#define PORT_HAS_UBSAN 0
#endif

#if defined(__has_feature)
	#if __has_feature(memory_sanitizer)
		#define PORT_HAS_MSAN 1
	#else
		#define PORT_HAS_MSAN 0
	#endif
#else
	#define PORT_HAS_MSAN 0
#endif

#define PORT_HAS_ANY_SANITIZER \
	(PORT_HAS_ASAN || PORT_HAS_TSAN || PORT_HAS_UBSAN || PORT_HAS_MSAN)
