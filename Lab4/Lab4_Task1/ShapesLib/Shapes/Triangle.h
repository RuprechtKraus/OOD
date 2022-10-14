#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(const Point& v1, const Point& v2, const Point& v3, Color color);
	Triangle(Point&& v1, Point&& v2, Point&& v3, Color color);

	void Draw(ICanvas& canvas) const override;
	Point GetVertex1() const noexcept;
	Point GetVertex2() const noexcept;
	Point GetVertex3() const noexcept;

private:
	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};