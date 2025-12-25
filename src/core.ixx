export module synodic.portability.core;

import std;

namespace port
{

// ============================================================================
// Platform Concept
// ============================================================================

export template<typename T>
concept platform_like = requires(const T& platform) {
	{ T::Name() } -> std::convertible_to<std::string_view>;
};

/// CRTP base class for platform backends
export class Platform
{
public:
	template<typename Self>
	constexpr bool Valid(this const Self&) noexcept
	{
		return !Self::Name().empty();
	}
};

// ============================================================================
// Compiler Concept
// ============================================================================

export template<typename T>
concept compiler_like = requires(const T& compiler) {
	{ T::Name() } -> std::convertible_to<std::string_view>;
	{ T::Version() } -> std::convertible_to<std::tuple<int, int, int>>;
};

/// CRTP base class for compiler backends
export class Compiler
{
public:
	template<typename Self>
	constexpr bool Valid(this const Self&) noexcept
	{
		return !Self::Name().empty();
	}

	template<typename Self>
	static constexpr int Major() noexcept
	{
		return std::get<0>(Self::Version());
	}

	template<typename Self>
	static constexpr int Minor() noexcept
	{
		return std::get<1>(Self::Version());
	}

	template<typename Self>
	static constexpr int Patch() noexcept
	{
		return std::get<2>(Self::Version());
	}
};

// ============================================================================
// Compiler Feature Traits (extensible without modifying core)
// ============================================================================

/// Trait: Compiler supports GNU-style inline assembly
export template<compiler_like C>
struct SupportsGnuAsm : std::false_type {};

/// Trait: Compiler supports [[gnu::always_inline]] attribute
export template<compiler_like C>
struct SupportsGnuAttributes : std::false_type {};

/// Trait: Compiler supports __forceinline
export template<compiler_like C>
struct SupportsForceInline : std::false_type {};

/// Trait: Compiler supports #pragma optimize
export template<compiler_like C>
struct SupportsPragmaOptimize : std::false_type {};

// ============================================================================
// Architecture Concept
// ============================================================================

export enum class ArchitectureType
{
	X86,
	X64,
	Arm,
	Arm64,
	Unknown
};

export template<typename T>
concept architecture_like = requires(const T& arch) {
	{ T::Name() } -> std::convertible_to<std::string_view>;
	{ T::Type() } -> std::convertible_to<ArchitectureType>;
	{ T::PointerSize() } -> std::convertible_to<std::size_t>;
};

/// CRTP base class for architecture backends
export class Architecture
{
public:
	template<typename Self>
	static constexpr bool Is64Bit() noexcept
	{
		return Self::PointerSize() == 8;
	}

	template<typename Self>
	static constexpr bool Is32Bit() noexcept
	{
		return Self::PointerSize() == 4;
	}
};

} // namespace port
