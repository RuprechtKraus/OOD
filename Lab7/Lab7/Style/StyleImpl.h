#pragma once
#include "Defaults.h"
#include <optional>

template <typename Base>
class StyleImpl : public Base
{
public:
	void Enable(bool enable) noexcept override
	{
		m_enabled = enable;
	}

	std::optional<bool> IsEnabled() const noexcept override
	{
		return m_enabled;
	}

	void SetColor(RGBAColor color) noexcept override
	{
		m_color = color;
	}

	std::optional<RGBAColor> GetColor() const noexcept override
	{
		return m_color;
	}

private:
	bool m_enabled = true;
	RGBAColor m_color = 0xFFFFFF;
};