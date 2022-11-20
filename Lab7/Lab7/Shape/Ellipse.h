#pragma once
#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(const Point& center, float horizontalRadius, float verticalRadius) noexcept;

private:
	void DrawImpl(ICanvas& canvas) const final;
	void AdjustShape(const FrameRect& oldFrame, double scaleFactorX, double scaleFactorY) final;

	Point m_center;
	float m_horizontalRadius;
	float m_verticalRadius;
};