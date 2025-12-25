export module synodic.portability.compiler.gcc;

import synodic.portability.core;

import std;

namespace port
{

export class GccCompiler : public Compiler
{
public:
	static constexpr std::string_view Name() noexcept
	{
		return "GCC";
	}

	static constexpr std::tuple<int, int, int> Version() noexcept
	{
#if defined(__GNUC__) && !defined(__clang__)
		return {__GNUC__, __GNUC_MINOR__, __GNUC_PATCHLEVEL__};
#else
		return {0, 0, 0};
#endif
	}
};

static_assert(compiler_like<GccCompiler>);

// Trait specializations for GCC
export template<>
struct SupportsGnuAsm<GccCompiler> : std::true_type {};

export template<>
struct SupportsGnuAttributes<GccCompiler> : std::true_type {};

export template<>
struct SupportsForceInline<GccCompiler> : std::false_type {};

export template<>
struct SupportsPragmaOptimize<GccCompiler> : std::false_type {};

} // namespace port
