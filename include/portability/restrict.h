#pragma once

#if defined(_MSC_VER)
#define PORT_RESTRICT __restrict
#elif defined(__clang__) || defined(__GNUC__)
#define PORT_RESTRICT __restrict__
#else
#define PORT_RESTRICT
#endif
