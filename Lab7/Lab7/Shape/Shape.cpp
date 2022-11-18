#include "Shape.h"

void Shape::SetFrame(const FrameRect& frame) noexcept
{
	int factorX = frame.width / m_frame.width;
	int factorY = frame.height / m_frame.height;
	m_frame = frame;
	AdjustScale(factorX, factorY);
}

std::optional<FrameRect> Shape::GetFrame() const
{
	return m_frame;
}

std::shared_ptr<ILineStyle> Shape::GetOutlineStyle()
{
	return m_lineStyle;
}

std::shared_ptr<const ILineStyle> Shape::GetOutlineStyle() const
{
	return m_lineStyle;
}

std::shared_ptr<IStyle> Shape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IStyle> Shape::GetFillStyle() const
{
	return m_fillStyle;
}