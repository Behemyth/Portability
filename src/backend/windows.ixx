export module synodic.portability.backend.windows;

import synodic.portability;

import std;

export class WindowsPlatform : public Platform
{
public:
	constexpr std::string_view name() const noexcept
	{
		return "Windows";
	}
};

// Verify it satisfies the concept at compile time
static_assert(platform_like<WindowsPlatform>);
