#pragma once
#include "ILineStyle.h"
#include "StyleImpl.h"

class LineStyle : public StyleImpl<ILineStyle>
{
public:
	std::optional<int> GetLineWidth() const noexcept override
	{
		return m_lineWidth;
	}

	void SetLineWidth(int width) noexcept override
	{
		m_lineWidth = width;
	}

private:
	std::optional<int> m_lineWidth;
};