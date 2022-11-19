#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point& topLeft, int width, int height);

private:
	void DrawImpl(ICanvas& canvas) const final;
	void AdjustShape(const FrameRect& oldFrame, double scaleFactorX, double scaleFactorY) final;

	Point m_topLeft;
	int m_width;
	int m_height;
};