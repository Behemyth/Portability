export module synodic.portability.compiler;

export import synodic.portability.compiler.msvc;
export import synodic.portability.compiler.clang;
export import synodic.portability.compiler.gcc;

import synodic.portability.core;

import std;

namespace port
{

namespace detail
{

consteval auto DetectCompiler() noexcept
{
#if defined(__clang__)
	return ClangCompiler{};
#elif defined(__GNUC__)
	return GccCompiler{};
#elif defined(_MSC_VER)
	return MsvcCompiler{};
#else
	static_assert(false, "Unknown compiler");
#endif
}

} // namespace detail

/// The compiler used to build this code, auto-detected at compile time
export inline constexpr auto CurrentCompiler = detail::DetectCompiler();

/// Type alias for the current compiler
export using CurrentCompilerType = decltype(CurrentCompiler);

// Convenience constants
export inline constexpr bool IsMsvc  = std::same_as<CurrentCompilerType, MsvcCompiler>;
export inline constexpr bool IsClang = std::same_as<CurrentCompilerType, ClangCompiler>;
export inline constexpr bool IsGcc   = std::same_as<CurrentCompilerType, GccCompiler>;

// Feature detection helpers using traits
export inline constexpr bool HasGnuAsm          = SupportsGnuAsm<CurrentCompilerType>::value;
export inline constexpr bool HasGnuAttributes   = SupportsGnuAttributes<CurrentCompilerType>::value;
export inline constexpr bool HasForceInline     = SupportsForceInline<CurrentCompilerType>::value;
export inline constexpr bool HasPragmaOptimize  = SupportsPragmaOptimize<CurrentCompilerType>::value;

} // namespace port
