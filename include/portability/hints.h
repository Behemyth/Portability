#pragma once

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

#if defined(__clang__) || defined(__GNUC__)
#define PORT_COLD [[gnu::cold]]
#define PORT_HOT  [[gnu::hot]]
#else
#define PORT_COLD
#define PORT_HOT
#endif

#if defined(__clang__) || defined(__GNUC__)
#define PORT_PURE  [[gnu::pure]]
#define PORT_CONST [[gnu::const]]
#else
#define PORT_PURE
#define PORT_CONST
#endif
