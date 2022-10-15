#include "ShapeFactory.h"
#include "Utils/StringUtils.h"

std::unique_ptr<Shape> ShapeFactory::CreateShape(const std::string& description)
{
	std::istringstream args(description);
	std::string type;
	std::unique_ptr<Shape> shape;
	args.exceptions(std::ios::failbit);

	args >> type;
	type = StringUtils::ToLower(type);

	if (type == "rectangle")
	{
		shape = CreateRectangle(args);
	}
	else if (type == "triangle")
	{
		shape = CreateTriangle(args);
	}
	else if (type == "ellipse")
	{
		shape = CreateEllipse(args);
	}
	else if (type == "regular_polygon")
	{
		shape = CreateRegularPolygon(args);
	}
	else
	{
		throw std::invalid_argument("Unknown shape");
	}

	return shape;
}

std::unique_ptr<Rectangle> ShapeFactory::CreateRectangle(std::istringstream& args)
{
	Point p1{};
	Point p2{};
	Color color;
	std::string colorStr;

	args >> p1.x >> p1.y;
	args >> p2.x >> p2.y;
	args >> colorStr;
	color = StringToColor(colorStr);

	return std::make_unique<Rectangle>(p1, p2, color);
}

std::unique_ptr<Triangle> ShapeFactory::CreateTriangle(std::istringstream& args)
{
	Point v1{};
	Point v2{};
	Point v3{};
	Color color;
	std::string colorStr;

	args >> v1.x >> v1.y;
	args >> v2.x >> v2.y;
	args >> v3.x >> v3.y;
	args >> colorStr;
	color = StringToColor(colorStr);

	return std::make_unique<Triangle>(v1, v2, v3, color);
}

std::unique_ptr<Ellipse> ShapeFactory::CreateEllipse(std::istringstream& args)
{
	Point center{};
	int width{}, height{};
	Color color;
	std::string colorStr;

	args >> center.x >> center.y;
	args >> width >> height;
	args >> colorStr;
	color = StringToColor(colorStr);

	return std::make_unique<Ellipse>(center, width, height, color);
}

std::unique_ptr<RegularPolygon> ShapeFactory::CreateRegularPolygon(std::istringstream& args)
{
	Point center{};
	int radius{}, vertexCount{};
	Color color;
	std::string colorStr;

	args >> center.x >> center.y;
	args >> radius >> vertexCount;
	args >> colorStr;
	color = StringToColor(colorStr);

	return std::make_unique<RegularPolygon>(center, radius, vertexCount, color);
}