#include "Rectangle.h"
#include <stdexcept>

Rectangle::Rectangle(const Point& topLeft, const Point& bottomRight, Color color)
	: Shape(color)
{
	if (!AreCornersCorrect(topLeft, bottomRight))
	{
		throw std::invalid_argument("Incorrect bottom right vertex positioning");
	}

	m_topLeft = topLeft;
	m_bottomRight = bottomRight;
}

Rectangle::Rectangle(Point&& topLeft, Point&& bottomRight, Color color)
	: Shape(color)
{
	if (!AreCornersCorrect(topLeft, bottomRight))
	{
		throw std::invalid_argument("Incorrect bottom right vertex positioning");
	}

	m_topLeft = std::move(topLeft);
	m_bottomRight = std::move(bottomRight);
}

bool Rectangle::AreCornersCorrect(const Point& topLeft, const Point& bottomRight) noexcept
{
	return bottomRight.x >= topLeft.x && bottomRight.y >= topLeft.y;
}

void Rectangle::Draw(ICanvas& canvas) const
{
	Point topRight{ m_bottomRight.x, m_topLeft.y };
	Point bottomLeft{ m_topLeft.x, m_bottomRight.y };

	canvas.SetColor(m_color);
	canvas.DrawLine(m_topLeft, topRight);
	canvas.DrawLine(topRight, m_bottomRight);
	canvas.DrawLine(m_bottomRight, bottomLeft);
	canvas.DrawLine(bottomLeft, m_topLeft);
}

Point Rectangle::GetTopLeft() const noexcept
{
	return m_topLeft;
}

Point Rectangle::GetBottomRight() const noexcept
{
	return m_bottomRight;
}