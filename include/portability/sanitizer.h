#pragma once

#if defined(NDEBUG)
#define PORT_HAS_ASSERTIONS 0
#else
#define PORT_HAS_ASSERTIONS 1
#endif

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
