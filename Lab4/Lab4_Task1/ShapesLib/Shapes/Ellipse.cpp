#include "Ellipse.h"

Ellipse::Ellipse(const Point& topLeft, int width, int height, Color color)
	: Shape(color)
	, m_topLeft(topLeft)
	, m_horizontalRadius(width)
	, m_verticalRadius(height)
{
}

Ellipse::Ellipse(Point&& topLeft, int width, int height, Color color)
	: Shape(color)
	, m_topLeft(std::move(topLeft))
	, m_horizontalRadius(width)
	, m_verticalRadius(height)
{
}

void Ellipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawEllipse(m_topLeft, m_horizontalRadius, m_verticalRadius);
}

Point Ellipse::GetCenter() const
{
	float x = m_topLeft.x + m_horizontalRadius / static_cast<float>(2);
	float y = m_topLeft.y + m_verticalRadius / static_cast<float>(2);

	return { x, y };
}

int Ellipse::GetHorizontalRadius() const noexcept
{
	return m_horizontalRadius;
}

int Ellipse::GetVerticalRadius() const noexcept
{
	return m_verticalRadius;
}