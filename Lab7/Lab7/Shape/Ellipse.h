#pragma once
#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(const Point& center, int horizontalRadius, int verticalRadius) noexcept;

private:
	void DrawImpl(ICanvas& canvas) const final;
	void AdjustShape(const FrameRect& oldFrame, double scaleFactorX, double scaleFactorY) final;

	Point m_center;
	int m_horizontalRadius;
	int m_verticalRadius;
};