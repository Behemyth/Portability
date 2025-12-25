export module synodic.portability.architecture;

import synodic.portability.core;

import std;

namespace port
{

// ============================================================================
// Architecture Backends (inline, no separate files needed)
// ============================================================================

export class X86Architecture : public Architecture
{
public:
	static constexpr std::string_view Name() noexcept { return "x86"; }
	static constexpr ArchitectureType Type() noexcept { return ArchitectureType::X86; }
	static constexpr std::size_t PointerSize() noexcept { return 4; }
};

export class X64Architecture : public Architecture
{
public:
	static constexpr std::string_view Name() noexcept { return "x64"; }
	static constexpr ArchitectureType Type() noexcept { return ArchitectureType::X64; }
	static constexpr std::size_t PointerSize() noexcept { return 8; }
};

export class ArmArchitecture : public Architecture
{
public:
	static constexpr std::string_view Name() noexcept { return "ARM"; }
	static constexpr ArchitectureType Type() noexcept { return ArchitectureType::Arm; }
	static constexpr std::size_t PointerSize() noexcept { return 4; }
};

export class Arm64Architecture : public Architecture
{
public:
	static constexpr std::string_view Name() noexcept { return "ARM64"; }
	static constexpr ArchitectureType Type() noexcept { return ArchitectureType::Arm64; }
	static constexpr std::size_t PointerSize() noexcept { return 8; }
};

export class UnknownArchitecture : public Architecture
{
public:
	static constexpr std::string_view Name() noexcept { return "Unknown"; }
	static constexpr ArchitectureType Type() noexcept { return ArchitectureType::Unknown; }
	static constexpr std::size_t PointerSize() noexcept { return sizeof(void*); }
};

static_assert(architecture_like<X86Architecture>);
static_assert(architecture_like<X64Architecture>);
static_assert(architecture_like<ArmArchitecture>);
static_assert(architecture_like<Arm64Architecture>);
static_assert(architecture_like<UnknownArchitecture>);

// ============================================================================
// Detection
// ============================================================================

namespace detail
{

consteval auto DetectArchitecture() noexcept
{
#if defined(_M_X64) || defined(__x86_64__) || defined(__amd64__)
	return X64Architecture{};
#elif defined(_M_IX86) || defined(__i386__) || defined(__i686__)
	return X86Architecture{};
#elif defined(_M_ARM64) || defined(__aarch64__)
	return Arm64Architecture{};
#elif defined(_M_ARM) || defined(__arm__)
	return ArmArchitecture{};
#else
	return UnknownArchitecture{};
#endif
}

} // namespace detail

/// The CPU architecture this code is compiled for
export inline constexpr auto CurrentArchitecture = detail::DetectArchitecture();

/// Type alias for the current architecture
export using CurrentArchitectureType = decltype(CurrentArchitecture);

// Convenience constants
export inline constexpr bool IsX86   = std::same_as<CurrentArchitectureType, X86Architecture>;
export inline constexpr bool IsX64   = std::same_as<CurrentArchitectureType, X64Architecture>;
export inline constexpr bool IsArm   = std::same_as<CurrentArchitectureType, ArmArchitecture>;
export inline constexpr bool IsArm64 = std::same_as<CurrentArchitectureType, Arm64Architecture>;

export inline constexpr bool Is32Bit = CurrentArchitecture.PointerSize() == 4;
export inline constexpr bool Is64Bit = CurrentArchitecture.PointerSize() == 8;

} // namespace port
