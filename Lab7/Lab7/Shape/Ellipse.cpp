#include "Ellipse.h"

Ellipse::Ellipse(const Point& center, float horizontalRadius, float verticalRadius) noexcept
	: m_center(center)
	, m_horizontalRadius(horizontalRadius)
	, m_verticalRadius(verticalRadius)
{
	m_frame = {
		{ m_center.x - m_horizontalRadius, m_center.y - m_verticalRadius },
		m_horizontalRadius * 2,
		m_verticalRadius * 2
	};
}

void Ellipse::DrawImpl(ICanvas& canvas) const
{
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

void Ellipse::AdjustShape(const FrameRect& oldFrame, double scaleFactorX, double scaleFactorY)
{
	m_center = {
		m_frame.topLeft.x + m_frame.width / 2,
		m_frame.topLeft.y + m_frame.height / 2
	};
	m_horizontalRadius *= scaleFactorX;
	m_verticalRadius *= scaleFactorY;
}