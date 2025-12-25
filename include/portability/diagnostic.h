#pragma once

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
