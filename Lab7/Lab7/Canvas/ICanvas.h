#pragma once
#include <vector>
#include "CommonTypes/Defaults.h"
#include "CommonTypes/Point.h"

class ICanvas
{
public:
	virtual void SetLineColor(RGBAColor color) = 0;
	virtual void SetFillColor(RGBAColor color) = 0;
	virtual void SetLineWidth(int width) = 0;

	virtual void DrawLine(const Point& from, const Point& to) const = 0;
	virtual void DrawPolygon(const std::vector<Point>& points) const = 0;
	virtual void DrawEllipse(const Point& center, int width, int height) const = 0;

	virtual ~ICanvas() = default;
};