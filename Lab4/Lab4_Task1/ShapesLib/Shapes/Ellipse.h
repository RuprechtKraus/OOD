#pragma once
#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(const Point& topLeft, int width, int height, Color color);
	Ellipse(Point&& topLeft, int width, int height, Color color);

	void Draw(ICanvas& canvas) const override;
	Point GetCenter() const;
	int GetHorizontalRadius() const noexcept;
	int GetVerticalRadius() const noexcept;

private:
	Point m_topLeft;
	int m_horizontalRadius;
	int m_verticalRadius;
};