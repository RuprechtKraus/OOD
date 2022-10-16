#include "RegularPolygon.h"
#include <cmath>
#include <numbers>
#include <vector>

namespace
{
constexpr inline double pi = std::numbers::pi;
}

RegularPolygon::RegularPolygon(const Point& center, int radius, int vertexCount, Color color)
	: Shape(color)
	, m_center(center)
{
	if (radius < 0)
	{
		throw std::invalid_argument("Radius can not be negative");
	}

	if (vertexCount < 3)
	{
		throw std::invalid_argument("Vertex count can not be less than 3");
	}

	m_radius = radius;
	m_vertexCount = vertexCount;
}

RegularPolygon::RegularPolygon(Point&& center, int radius, int vertexCount, Color color)
	: Shape(color)
	, m_center(std::move(center))
{
	if (radius < 0)
	{
		throw std::invalid_argument("Radius can not be negative");
	}

	if (vertexCount < 3)
	{
		throw std::invalid_argument("Vertex count can not be less than 3");
	}

	m_radius = radius;
	m_vertexCount = vertexCount;
}

void RegularPolygon::Draw(ICanvas& canvas) const
{
	std::vector<Point> vertices{ FindVertexCoordinates() };
	size_t nextIndex{};
	canvas.SetColor(m_color);

	for (size_t index = 0; index < vertices.size(); index++)
	{
		nextIndex = index + 1 < vertices.size() ? index + 1 : 0;
		canvas.DrawLine(vertices[index], vertices[nextIndex]);
	}
}

std::vector<Point> RegularPolygon::FindVertexCoordinates() const
{
	double angle{ 2 * pi / m_vertexCount };
	std::vector<Point> vertices;
	vertices.reserve(m_vertexCount);

	for (size_t i = 0; i < m_vertexCount; i++)
	{
		float x = m_center.x + m_radius * static_cast<float>(std::cos(i * angle));
		float y = m_center.y + m_radius * static_cast<float>(std::sin(i * angle));
		vertices.emplace_back(x, y);
	}

	return vertices;
}

Point RegularPolygon::GetCenter() const noexcept
{
	return m_center;
}

int RegularPolygon::GetVertexCount() const noexcept
{
	return m_vertexCount;
}

int RegularPolygon::GetRadius() const noexcept
{
	return m_radius;
}