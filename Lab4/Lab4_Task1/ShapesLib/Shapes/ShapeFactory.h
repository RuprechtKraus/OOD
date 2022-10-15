#pragma once
#include "Ellipse.h"
#include "IShapeFactory.h"
#include "Rectangle.h"
#include "RegularPolygon.h"
#include "Triangle.h"
#include <memory>
#include <sstream>

class ShapeFactory : public IShapeFactory
{
public:
	std::unique_ptr<Shape> CreateShape(const std::string& description) override;

private:
	static std::unique_ptr<Rectangle> CreateRectangle(std::istringstream& args);
	static std::unique_ptr<Triangle> CreateTriangle(std::istringstream& args);
	static std::unique_ptr<Ellipse> CreateEllipse(std::istringstream& args);
	static std::unique_ptr<RegularPolygon> CreateRegularPolygon(std::istringstream& args);
};