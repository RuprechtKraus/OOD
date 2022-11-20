#include "Rectangle.h"

Rectangle::Rectangle(const Point& topLeft, float width, float height) noexcept
	: m_topLeft(topLeft)
	, m_width(width)
	, m_height(height)
{
	m_frame = { m_topLeft, m_width, m_height };
}

void Rectangle::DrawImpl(ICanvas& canvas) const
{
	canvas.DrawPolygon({ m_topLeft,
		{ m_topLeft.x + m_width, m_topLeft.y },
		{ m_topLeft.x + m_width, m_topLeft.y + m_height },
		{ m_topLeft.x, m_topLeft.y + m_height } });
}

void Rectangle::AdjustShape(const FrameRect& oldFrame, double scaleFactorX, double scaleFactorY)
{
	m_topLeft = m_frame.topLeft;
	m_width = m_frame.width;
	m_height = m_frame.height;
}