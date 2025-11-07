export module synodic.portability.backend.linux;

import synodic.portability;

import std;

export class LinuxPlatform : public Platform
{
public:
	constexpr std::string_view name() const noexcept
	{
		return "Linux";
	}
};

// Verify it satisfies the concept at compile time
static_assert(platform_like<LinuxPlatform>);
