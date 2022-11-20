#include "GroupLineStyle.h"

GroupLineStyle::GroupLineStyle(LineStyleEnumerator&& enumerator)
	: GroupStyleImpl(std::move(enumerator))
{
}

void GroupLineStyle::SetLineWidth(int width)
{
	m_enumerator([=](BaseStyle& style) {
		style.SetLineWidth(width);
	});
}

std::optional<int> GroupLineStyle::GetLineWidth() const
{
	std::optional<int> lineWidth;

	m_enumerator([&lineWidth, isConsistent = false](BaseStyle& style) mutable {
		if (!isConsistent)
		{
			lineWidth = style.GetLineWidth();
			isConsistent = true;
		}
		else if (lineWidth != style.GetLineWidth())
		{
			lineWidth = std::nullopt;
			return;
		}
	});

	return lineWidth;
}