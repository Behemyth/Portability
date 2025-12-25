export module synodic.portability.architecture;

import std;

namespace port
{

	// Unique identifier for compile-time architecture checks
	export inline constexpr std::string_view ArchitectureID = "arm";

	// Human-readable architecture name for display/logging
	export consteval std::string_view ArchitectureName() noexcept { return "ARM"; }

	// Size of a pointer in bytes
	export inline constexpr std::size_t PointerSize = 4;

}
