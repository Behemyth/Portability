#pragma once

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
