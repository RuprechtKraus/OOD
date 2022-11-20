#pragma once
#include "Defaults.h"
#include <optional>

template <typename BaseStyle, typename Enumerator>
class GroupStyleImpl : public BaseStyle
{
public:
	explicit GroupStyleImpl(Enumerator&& enumerator)
		: m_enumerator(enumerator)
	{
	}

	void Enable(bool enable) override
	{
		m_enumerator([](BaseStyle& style) {
			style->Enable(enable);
		});
	}

	std::optional<bool> IsEnabled() const noexcept override
	{
		throw std::exception();
	}

	void SetColor(RGBAColor color) noexcept override
	{
		throw std::exception();
	}

	std::optional<RGBAColor> GetColor() const noexcept override
	{
		throw std::exception();
	}

protected:
	Enumerator m_enumerator;
};