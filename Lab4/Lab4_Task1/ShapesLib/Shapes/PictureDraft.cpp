#include "PictureDraft.h"

void PictureDraft::AddShape(std::unique_ptr<Shape>&& shape)
{
	m_shapes.push_back(std::move(shape));
}

bool PictureDraft::IsEmpty() const noexcept
{
	return m_shapes.empty();
}

size_t PictureDraft::GetShapeCount() const noexcept
{
	return m_shapes.size();
}

const Shape& PictureDraft::GetShape(size_t index) const
{
	return *m_shapes.at(index);
}

PictureDraft::ConstIterator PictureDraft::begin() const
{
	return m_shapes.begin();
}

PictureDraft::ConstIterator PictureDraft::end() const
{
	return m_shapes.end();
}