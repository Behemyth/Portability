#pragma once

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
