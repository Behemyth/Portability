export module synodic.portability;

import std;

export template<typename T>
concept platform_like = requires(const T& platform) {
	{ platform.name() } -> std::convertible_to<std::string_view>;
};

// TODO: Generate from concept
export class Platform
{
public:
	template<typename Self>
	constexpr bool Valid(this const Self& self) noexcept
	{
		return !self.name().empty();
	}

	template<typename Self>
	constexpr std::string_view Name(this const Self& self) noexcept
	{
		return self.name();
	}
};

// TODO: Generate from concept
export class PlatformProxy
{
private:
	struct Concept
	{
		virtual ~Concept()							   = default;
		virtual std::string_view name() const noexcept = 0;
	};

	template<platform_like T>
	struct Model final : Concept
	{
		T platform;

		constexpr explicit Model(T p) :
			platform(std::move(p))
		{
		}

		std::string_view name() const noexcept override
		{
			return platform.name();
		}
	};

	std::unique_ptr<Concept> impl;

public:
	template<platform_like T>
	constexpr PlatformProxy(T platform) :
		impl(std::make_unique<Model<T>>(std::move(platform)))
	{
	}

	std::string_view name() const noexcept
	{
		return impl->name();
	}
};
