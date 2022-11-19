#include "Shape.h"

void Shape::SetFrame(const FrameRect& frame) noexcept
{
	FrameRect oldFrame = m_frame;
	double factorX = static_cast<double>(frame.width) / m_frame.width;
	double factorY = static_cast<double>(frame.height) / m_frame.height;
	m_frame = frame;
	AdjustShape(oldFrame, factorX, factorY);
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