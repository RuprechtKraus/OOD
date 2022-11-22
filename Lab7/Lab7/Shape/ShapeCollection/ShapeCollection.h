#pragma once
#include "IShapeCollection.h"
#include <stdexcept>
#include <vector>

class ShapeCollection : public IShapeCollection
{
public:
	size_t GetShapeCount() const override;

	void InsertShape(const std::shared_ptr<IShape>& shape, std::optional<size_t> position) override;
	void RemoveShape(size_t position) override;

	std::shared_ptr<IShape> GetShapeAt(size_t position) override;
	std::shared_ptr<const IShape> GetShapeAt(size_t position) const override;

protected:
	std::vector<std::shared_ptr<IShape>> m_shapes;

private:
	void AssertIndexWithinRangeExclusive(size_t index) const;
	void AssertIndexWithinRangeInclusive(size_t index) const;
};