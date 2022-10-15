#pragma once
#include "Color.h"
#include "Point.h"

class ICanvas
{
public:
	virtual void SetColor(Color color) = 0;
	virtual void DrawLine(const Point& from, const Point& to) = 0;
	virtual void DrawEllipse(const Point& center, int width, int height) = 0;

	virtual ~ICanvas() = default;
};