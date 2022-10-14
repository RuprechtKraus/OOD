#pragma once
#include "Shape.h"
#include "Point.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point& topLeft, const Point& bottomRight, Color color);
	Rectangle(Point&& topLeft, Point&& bottomRight, Color color);

	void Draw(ICanvas& canvas) const override;
	Point GetTopLeft() const noexcept;
	Point GetBottomRight() const noexcept;

private:
	static bool AreCornersCorrect(const Point& topLeft, const Point& bottomRight) noexcept;

	Point m_topLeft;
	Point m_bottomRight;
};