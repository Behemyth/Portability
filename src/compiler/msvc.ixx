export module synodic.portability.compiler;

import std;

namespace port
{

// Unique identifier for compile-time compiler checks
export inline constexpr std::string_view CompilerId = "msvc";

// Human-readable compiler name for display/logging
export consteval std::string_view CompilerName() noexcept { return "MSVC"; }

export consteval std::tuple<int, int, int> CompilerVersion() noexcept
{
	return {
		_MSC_VER / 100,
		_MSC_VER % 100,
#if defined(_MSC_FULL_VER)
		_MSC_FULL_VER % 100000
#else
		0
#endif
	};
}

// Compiler capabilities
export inline constexpr bool HasGnuAsm         = false;
export inline constexpr bool HasGnuAttributes  = false;
export inline constexpr bool HasForceInline    = true;
export inline constexpr bool HasPragmaOptimize = true;

}
