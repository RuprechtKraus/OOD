#pragma once
#include "Shapes/Shape.h"

class MockShape : public Shape
{
public:
	MockShape(Color color)
		: Shape(color)
	{
	}

	void Draw(ICanvas& canvas) const override
	{
	}
};