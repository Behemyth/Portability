export module synodic.portability.platform.linux;

import synodic.portability.core;

import std;

namespace port
{

export class LinuxPlatform : public Platform
{
public:
	static constexpr std::string_view Name() noexcept
	{
		return "Linux";
	}
};

static_assert(platform_like<LinuxPlatform>);

} // namespace port
