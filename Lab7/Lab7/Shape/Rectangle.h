#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point& topLeft, float width, float height) noexcept;

private:
	void DrawImpl(ICanvas& canvas) const final;
	void AdjustShape(const FrameRect& oldFrame, double scaleFactorX, double scaleFactorY) final;

	Point m_topLeft;
	float m_width;
	float m_height;
};