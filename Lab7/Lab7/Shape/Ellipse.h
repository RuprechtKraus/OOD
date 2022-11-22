#pragma once
#include "Shape.h"

class Ellipse : public Shape
{
public:
	Ellipse(const Point& center, float horizontalRadius, float verticalRadius) noexcept;

	void SetFrame(const FrameRect& frame) noexcept override;

private:
	void DrawImpl(ICanvas& canvas) const final;
};