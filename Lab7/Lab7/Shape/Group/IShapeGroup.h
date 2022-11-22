#pragma once
#include "Shape/IShape.h"
#include "Shape/ShapeCollection/IShapeCollection.h"
#include <memory>
#include <optional>

class IShapeGroup : public IShape
	, public IShapeCollection
	, public std::enable_shared_from_this<IShapeGroup>
{
public:
	virtual ~IShapeGroup() = default;
};