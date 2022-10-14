#pragma once
#include "Shape.h"
#include <memory>
#include <string>

struct IShapeFactory
{
	virtual std::unique_ptr<Shape> CreateShape(const std::string& description) = 0;

	virtual ~IShapeFactory() = default;
};