export module synodic.portability.platform;

export import synodic.portability.platform.windows;
export import synodic.portability.platform.linux;
export import synodic.portability.platform.macos;

import synodic.portability.core;

import std;

namespace port
{

namespace detail
{

consteval auto DetectPlatform() noexcept
{
#if defined(_WIN32) || defined(_WIN64)
	return WindowsPlatform{};
#elif defined(__linux__)
	return LinuxPlatform{};
#elif defined(__APPLE__) && defined(__MACH__)
	return MacOSPlatform{};
#else
	static_assert(false, "Unknown platform");
#endif
}

} // namespace detail

/// The platform this code is compiled for, auto-detected at compile time
export inline constexpr auto CurrentPlatform = detail::DetectPlatform();

/// Type alias for the current platform
export using CurrentPlatformType = decltype(CurrentPlatform);

// Convenience constants
export inline constexpr bool IsWindows = std::same_as<CurrentPlatformType, WindowsPlatform>;
export inline constexpr bool IsLinux   = std::same_as<CurrentPlatformType, LinuxPlatform>;
export inline constexpr bool IsMacOS   = std::same_as<CurrentPlatformType, MacOSPlatform>;

} // namespace port
