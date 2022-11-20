#pragma once
#include "Defaults.h"
#include <optional>

#include <iostream>

template <typename BaseStyle, typename Enumerator>
class GroupStyleImpl : public BaseStyle
{
public:
	explicit GroupStyleImpl(Enumerator&& enumerator)
		: m_enumerator(std::move(enumerator))
	{
	}

	void Enable(bool enable) override
	{
		m_enumerator([=](BaseStyle& style) {
			style.Enable(enable);
		});
	}

	std::optional<bool> IsEnabled() const noexcept override
	{
		std::optional<bool> isEnabled;

		m_enumerator([&isEnabled, isConsistent = false](BaseStyle& style) mutable {
			if (!isConsistent)
			{
				isEnabled = style.IsEnabled();
				isConsistent = true;
			}
			else if (isEnabled != style.IsEnabled())
			{
				isEnabled = std::nullopt;
				return;
			}
		});

		return isEnabled;
	}

	void SetColor(RGBAColor color) noexcept override
	{
		m_enumerator([=](BaseStyle& style) {
			style.SetColor(color);
		});
	}

	std::optional<RGBAColor> GetColor() const noexcept override
	{
		std::optional<RGBAColor> color;

		m_enumerator([&color, isConsistent = false](BaseStyle& style) mutable {
			if (!isConsistent)
			{
				color = style.GetColor();
				isConsistent = true;
			}
			else if (color != style.GetColor())
			{
				color = std::nullopt;
				return;
			}
		});

		return color;
	}

protected:
	Enumerator m_enumerator;
};