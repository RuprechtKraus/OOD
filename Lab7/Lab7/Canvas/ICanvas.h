#pragma once
#include "Common/Point.h"
#include "Defaults.h"
#include <optional>
#include <vector>

class ICanvas
{
public:
	virtual void SetLineColor(std::optional<RGBAColor> color) = 0;
	virtual void SetFillColor(std::optional<RGBAColor> color) = 0;
	virtual void SetLineWidth(std::optional<int> width) = 0;

	virtual void DrawLine(const Point& from, const Point& to) const = 0;
	virtual void DrawPolygon(const std::vector<Point>& points) const = 0;
	virtual void DrawEllipse(const Point& center, int width, int height) const = 0;

	virtual ~ICanvas() = default;
};