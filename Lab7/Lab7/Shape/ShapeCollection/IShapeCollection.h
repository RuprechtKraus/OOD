#pragma once
#include "Shape/IShape.h"
#include <memory>
#include <optional>

class IShapeCollection
{
public:
	virtual size_t GetShapeCount() const = 0;
	virtual bool IsEmpty() const = 0;

	virtual void InsertShape(const std::shared_ptr<IShape>& shape, std::optional<size_t> position) = 0;
	virtual void RemoveShape(size_t position) = 0;

	virtual std::shared_ptr<IShape> GetShapeAt(size_t position) = 0;
	virtual std::shared_ptr<const IShape> GetShapeAt(size_t position) const = 0;

	virtual ~IShapeCollection() = default;
};