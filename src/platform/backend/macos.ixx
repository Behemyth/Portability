export module synodic.portability.platform.macos;

import synodic.portability.core;

import std;

namespace port
{

export class MacOSPlatform : public Platform
{
public:
	static constexpr std::string_view Name() noexcept
	{
		return "macOS";
	}
};

static_assert(platform_like<MacOSPlatform>);

} // namespace port
