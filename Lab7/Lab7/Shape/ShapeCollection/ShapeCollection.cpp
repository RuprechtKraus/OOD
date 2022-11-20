#include "ShapeCollection.h"

size_t ShapeCollection::GetShapeCount() const
{
	return m_shapes.size();
}

bool ShapeCollection::IsEmpty() const noexcept
{
	return m_shapes.empty();
}

void ShapeCollection::InsertShape(const std::shared_ptr<IShape>& shape, std::optional<size_t> position)
{
	size_t offset = position.value_or(m_shapes.size());
	AssertIndexWithinRangeExclusive(offset);
	m_shapes.insert(m_shapes.begin() + offset, shape);
}

void ShapeCollection::RemoveShape(size_t position)
{
	AssertIndexWithinRangeInclusive(position);
	m_shapes.erase(m_shapes.begin() + position);
}

std::shared_ptr<IShape> ShapeCollection::GetShapeAt(size_t position)
{
	AssertIndexWithinRangeInclusive(position);
	return m_shapes[position];
}

std::shared_ptr<const IShape> ShapeCollection::GetShapeAt(size_t position) const
{
	AssertIndexWithinRangeInclusive(position);
	return m_shapes.at(position);
}

void ShapeCollection::AssertIndexWithinRangeExclusive(size_t index) const
{
	if (index > m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
}

void ShapeCollection::AssertIndexWithinRangeInclusive(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
}