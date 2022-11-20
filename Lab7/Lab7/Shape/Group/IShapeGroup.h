#pragma once
#include "Shape/IShape.h"
#include "Shape/ShapeCollection/IShapeCollection.h"
#include <memory>
#include <optional>

class IShapeGroup : public IShape
	, public IShapeCollection
{
public:
	virtual ~IShapeGroup() = default;
};