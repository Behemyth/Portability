export module synodic.portability.compiler;

import std;

namespace port
{

// Unique identifier for compile-time compiler checks
export inline constexpr std::string_view CompilerId = "unknown";

// Human-readable compiler name for display/logging
export consteval std::string_view CompilerName() noexcept { return "Unknown"; }

export consteval std::tuple<int, int, int> CompilerVersion() noexcept
{
	return {0, 0, 0};
}

// Compiler capabilities
export inline constexpr bool HasGnuAsm         = false;
export inline constexpr bool HasGnuAttributes  = false;
export inline constexpr bool HasForceInline    = false;
export inline constexpr bool HasPragmaOptimize = false;

}
