#include "Triangle.h"

Triangle::Triangle(const Point& v1, const Point& v2, const Point& v3, Color color)
	: Shape(color)
	, m_vertex1(v1)
	, m_vertex2(v2)
	, m_vertex3(v3)
{
}

Triangle::Triangle(Point&& v1, Point&& v2, Point&& v3, Color color)
	: Shape(color)
	, m_vertex1(std::move(v1))
	, m_vertex2(std::move(v2))
	, m_vertex3(std::move(v3))
{
}

void Triangle::Draw(ICanvas& canvas) const
{
	canvas.SetColor(m_color);
	canvas.DrawLine(m_vertex1, m_vertex2);
	canvas.DrawLine(m_vertex2, m_vertex3);
	canvas.DrawLine(m_vertex3, m_vertex1);
}

Point Triangle::GetVertex1() const noexcept
{
	return m_vertex1;
}

Point Triangle::GetVertex2() const noexcept
{
	return m_vertex2;
}
Point Triangle::GetVertex3() const noexcept
{
	return m_vertex3;
}