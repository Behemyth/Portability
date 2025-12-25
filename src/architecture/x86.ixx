export module synodic.portability.architecture;

import std;

namespace port
{

	// Unique identifier for compile-time architecture checks
	export inline constexpr std::string_view ArchitectureID = "x86";

	// Human-readable architecture name for display/logging
	export consteval std::string_view ArchitectureName() noexcept { return "x86"; }

	// Size of a pointer in bytes
	export inline constexpr std::size_t PointerSize = 4;

}
