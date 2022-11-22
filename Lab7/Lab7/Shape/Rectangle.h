#pragma once
#include "Shape.h"

class Rectangle : public Shape
{
public:
	Rectangle(const Point& topLeft, float width, float height) noexcept;

	void SetFrame(const FrameRect& frame) noexcept override;

private:
	void DrawImpl(ICanvas& canvas) const final;
};