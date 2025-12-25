#pragma once

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
