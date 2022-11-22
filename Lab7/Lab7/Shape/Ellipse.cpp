#include "Ellipse.h"

Ellipse::Ellipse(const Point& center, float horizontalRadius, float verticalRadius) noexcept
{
	m_frame = {
		{ center.x - horizontalRadius, center.y - verticalRadius },
		horizontalRadius * 2,
		verticalRadius * 2
	};
}

void Ellipse::SetFrame(const FrameRect& frame) noexcept
{
	m_frame = frame;
}

void Ellipse::DrawImpl(ICanvas& canvas) const
{
	Point center = {
		m_frame.topLeft.x + m_frame.width / 2,
		m_frame.topLeft.y + m_frame.height / 2
	};
	canvas.DrawEllipse(center, m_frame.width, m_frame.height);
}