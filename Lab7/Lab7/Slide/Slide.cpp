#include "Slide.h"

void Slide::Draw(ICanvas& canvas) const
{
	for (size_t i = 0; i < m_shapes->GetShapeCount(); i++)
	{
		m_shapes->GetShapeAt(i)->Draw(canvas);
	}
}

IShapeCollection& Slide::GetShapes() noexcept
{
	return *m_shapes;
}