export module synodic.portability.compiler.clang;

import synodic.portability.core;

import std;

namespace port
{

export class ClangCompiler : public Compiler
{
public:
	static constexpr std::string_view Name() noexcept
	{
		return "Clang";
	}

	static constexpr std::tuple<int, int, int> Version() noexcept
	{
#if defined(__clang__)
		return {__clang_major__, __clang_minor__, __clang_patchlevel__};
#else
		return {0, 0, 0};
#endif
	}
};

static_assert(compiler_like<ClangCompiler>);

// Trait specializations for Clang
// Note: Clang supports GNU asm even when targeting Windows (Clang-CL)
export template<>
struct SupportsGnuAsm<ClangCompiler> : std::true_type {};

export template<>
struct SupportsGnuAttributes<ClangCompiler> : std::true_type {};

export template<>
struct SupportsForceInline<ClangCompiler> : std::false_type {};

export template<>
struct SupportsPragmaOptimize<ClangCompiler> : std::false_type {};

} // namespace port
