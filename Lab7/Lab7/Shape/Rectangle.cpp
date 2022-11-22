#include "Rectangle.h"

Rectangle::Rectangle(const Point& topLeft, float width, float height) noexcept
{
	m_frame = { topLeft, width, height };
}

void Rectangle::SetFrame(const FrameRect& frame) noexcept
{
	m_frame = frame;
}

void Rectangle::DrawImpl(ICanvas& canvas) const
{
	auto topLeft = m_frame.topLeft;
	auto width = m_frame.width;
	auto height = m_frame.height;

	canvas.DrawPolygon({ topLeft,
		{ topLeft.x + width, topLeft.y },
		{ topLeft.x + width, topLeft.y + height },
		{ topLeft.x, topLeft.y + height } });
}
