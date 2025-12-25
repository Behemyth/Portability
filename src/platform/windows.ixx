export module synodic.portability.platform;

import std;

namespace port
{

	// Unique identifier for compile-time platform checks
	export inline constexpr std::string_view PlatformID = "windows";

	// Human-readable platform name for display/logging
	export consteval std::string_view PlatformName() noexcept { return "Windows"; }

}
