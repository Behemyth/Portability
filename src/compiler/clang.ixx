export module synodic.portability.compiler;

import std;

namespace port
{

// Unique identifier for compile-time compiler checks
export inline constexpr std::string_view CompilerId = "clang";

// Human-readable compiler name for display/logging
export consteval std::string_view CompilerName() noexcept { return "Clang"; }

export consteval std::tuple<int, int, int> CompilerVersion() noexcept
{
	return {__clang_major__, __clang_minor__, __clang_patchlevel__};
}

// Compiler capabilities
export inline constexpr bool HasGnuAsm         = true;
export inline constexpr bool HasGnuAttributes  = true;
export inline constexpr bool HasForceInline    = false;
export inline constexpr bool HasPragmaOptimize = false;

}
