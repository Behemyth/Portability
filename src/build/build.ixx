export module synodic.portability.build;

import std;

namespace port
{

	// ============================================================================
	// Assertions Detection
	// ============================================================================

	/// Whether assertions (assert()) are enabled in this build
	export inline constexpr bool HasAssertions =
#if defined(NDEBUG)
		false;
#else
		true;
#endif

	// ============================================================================
	// Sanitizer Detection
	// ============================================================================

	export inline constexpr bool HasAddressSanitizer =
#if defined(__SANITIZE_ADDRESS__)
		true;
#elif defined(__has_feature)
		__has_feature(address_sanitizer);
#else
		false;
#endif

	export inline constexpr bool HasThreadSanitizer =
#if defined(__SANITIZE_THREAD__)
		true;
#elif defined(__has_feature)
		__has_feature(thread_sanitizer);
#else
		false;
#endif

	export inline constexpr bool HasUndefinedBehaviorSanitizer =
#if defined(__has_feature)
		__has_feature(undefined_behavior_sanitizer);
#else
		false;
#endif

	export inline constexpr bool HasMemorySanitizer =
#if defined(__has_feature)
		__has_feature(memory_sanitizer);
#else
		false;
#endif

	export inline constexpr bool HasAnySanitizer =
		HasAddressSanitizer || HasThreadSanitizer ||
		HasUndefinedBehaviorSanitizer || HasMemorySanitizer;

} // namespace port
