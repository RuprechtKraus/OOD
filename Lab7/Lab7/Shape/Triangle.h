#pragma once
#include "Shape.h"

class Triangle : public Shape
{
public:
	Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3) noexcept;

private:
	void DrawImpl(ICanvas& canvas) const final;
	void AdjustShape(const FrameRect& oldFrame, double scaleFactorX, double scaleFactorY) final;
	static Point AdjustPoint(
		const Point& point, 
		const FrameRect& oldFrame, 
		const FrameRect& newFrame, 
		double scaleFactorX, 
		double scaleFactorY);

	Point m_vertex1;
	Point m_vertex2;
	Point m_vertex3;
};