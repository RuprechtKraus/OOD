#pragma once
#include "Shapes/Ellipse.h"
#include "Shapes/IShapeFactory.h"
#include "Shapes/Rectangle.h"
#include "Shapes/RegularPolygon.h"
#include "Shapes/Triangle.h"

class MockFactory : public IShapeFactory
{
public:
	std::unique_ptr<Shape> CreateShape(const std::string& shape) override
	{
		if (shape == "rectangle")
		{
			return std::make_unique<Rectangle>(
				Point{ 0, 0 }, Point{ 1, 1 }, Color::Black);
		}
		else if (shape == "triangle")
		{
			return std::make_unique<Triangle>(
				Point{ 0, 0 }, Point{ 1, 0 }, Point{ 1, 1 }, Color::Black);
		}
		else if (shape == "ellipse")
		{
			return std::make_unique<Ellipse>(Point{ 0, 0 }, 1, 1, Color::Black);
		}
		else if (shape == "regular_polygon")
		{
			return std::make_unique<RegularPolygon>(Point{ 0, 0 }, 1, 4, Color::Black);
		}
		else
		{
			throw std::invalid_argument("Unknown shape");
		}
	}
};