#include "Ellipse.h"

Ellipse::Ellipse(const Point& center, int width, int height, Color color)
	: Shape(color)
	, m_center(center)
{
	if (width < 0 || height < 0)
	{
		throw std::invalid_argument("Radius can not be negative");
	}

	m_horizontalRadius = width;
	m_verticalRadius = height;
}

Ellipse::Ellipse(Point&& center, int width, int height, Color color)
	: Shape(color)
	, m_center(std::move(center))
{
	if (width < 0 || height < 0)
	{
		throw std::invalid_argument("Radius can not be negative");
	}

	m_horizontalRadius = width;
	m_verticalRadius = height;
}

void Ellipse::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawEllipse(m_center, m_horizontalRadius, m_verticalRadius);
}

Point Ellipse::GetCenter() const
{
	return m_center;
}

int Ellipse::GetHorizontalRadius() const noexcept
{
	return m_horizontalRadius;
}

int Ellipse::GetVerticalRadius() const noexcept
{
	return m_verticalRadius;
}