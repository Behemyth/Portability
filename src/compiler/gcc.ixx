export module synodic.portability.compiler;

import std;

namespace port
{

	// Unique identifier for compile-time compiler checks
	export inline constexpr std::string_view CompilerID = "gcc";

	// Human-readable compiler name for display/logging
	export consteval std::string_view CompilerName() noexcept { return "GCC"; }

	export consteval std::tuple<int, int, int> CompilerVersion() noexcept
	{
		return { __GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__ };
	}

	// Compiler capabilities
	export inline constexpr bool HasGnuAsm = true;
	export inline constexpr bool HasGnuAttributes = true;
	export inline constexpr bool HasForceInline = false;
	export inline constexpr bool HasPragmaOptimize = false;

}
