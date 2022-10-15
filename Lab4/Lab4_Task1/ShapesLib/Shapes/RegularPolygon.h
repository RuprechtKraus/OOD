#pragma once
#include "Shape.h"
#include <vector>

class RegularPolygon : public Shape
{
public:
	RegularPolygon(const Point& center, int radius, int vertexCount, Color color);
	RegularPolygon(Point&& center, int radius, int vertexCount, Color color);

	void Draw(ICanvas& canvas) const override;
	Point GetCenter() const noexcept;
	int GetVertexCount() const noexcept;
	int GetRadius() const noexcept;

private:
	std::vector<Point> FindVertexCoordinates() const;

	Point m_center;
	int m_radius;
	int m_vertexCount;
};