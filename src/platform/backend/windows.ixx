export module synodic.portability.platform.windows;

import synodic.portability.core;

import std;

namespace port
{

export class WindowsPlatform : public Platform
{
public:
	static constexpr std::string_view Name() noexcept
	{
		return "Windows";
	}
};

static_assert(platform_like<WindowsPlatform>);

} // namespace port
