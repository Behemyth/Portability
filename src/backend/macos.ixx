export module synodic.portability.backend.macos;

import synodic.portability;

import std;

export class MacOSPlatform : public Platform
{
public:
	constexpr std::string_view name() const noexcept
	{
		return "macOS";
	}
};

// Verify it satisfies the concept at compile time
static_assert(platform_like<MacOSPlatform>);
