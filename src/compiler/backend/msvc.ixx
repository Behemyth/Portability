export module synodic.portability.compiler.msvc;

import synodic.portability.core;

import std;

namespace port
{

export class MsvcCompiler : public Compiler
{
public:
	static constexpr std::string_view Name() noexcept
	{
		return "MSVC";
	}

	static constexpr std::tuple<int, int, int> Version() noexcept
	{
#if defined(_MSC_VER)
		return {
			_MSC_VER / 100,       // major (e.g., 19 for VS 2015+)
			_MSC_VER % 100,       // minor
	#if defined(_MSC_FULL_VER)
			_MSC_FULL_VER % 100000 // patch
	#else
			0
	#endif
		};
#else
		return {0, 0, 0};
#endif
	}
};

static_assert(compiler_like<MsvcCompiler>);

// Trait specializations for MSVC
export template<>
struct SupportsGnuAsm<MsvcCompiler> : std::false_type {};

export template<>
struct SupportsGnuAttributes<MsvcCompiler> : std::false_type {};

export template<>
struct SupportsForceInline<MsvcCompiler> : std::true_type {};

export template<>
struct SupportsPragmaOptimize<MsvcCompiler> : std::true_type {};

} // namespace port
