#include "ShapeGroup.h"
#include <algorithm>
#include <stdexcept>

ShapeGroup::ShapeGroup()
{
	// TODO: Добавить инициализацию стилей
}

void ShapeGroup::Draw(ICanvas& canvas) const
{
	for (const auto& shape : m_shapes)
	{
		shape->Draw(canvas);
	}
}

size_t ShapeGroup::GetShapeCount() const
{
	return m_shapes.size();
}

void ShapeGroup::InsertShape(
	const std::shared_ptr<IShape>& shape,
	std::optional<size_t> position)
{
	size_t offset = position.value_or(m_shapes.size());
	AssertIndexWithinRangeExclusive(offset);
	m_shapes.insert(m_shapes.begin() + offset, shape);
	ReevaluateFrame();
}

void ShapeGroup::RemoveShape(size_t position)
{
	AssertIndexWithinRangeInclusive(position);
	m_shapes.erase(m_shapes.begin() + position);
}

std::shared_ptr<IShape> ShapeGroup::GetShapeAt(size_t position)
{
	AssertIndexWithinRangeInclusive(position);
	return m_shapes[position];
}

std::shared_ptr<const IShape> ShapeGroup::GetShapeAt(size_t position) const
{
	AssertIndexWithinRangeInclusive(position);
	return m_shapes.at(position);
}

void ShapeGroup::SetFrame(const FrameRect& frame)
{
	if (m_shapes.empty())
	{
		throw std::logic_error("Cannot set frame of empty group");
	}

	FrameRect groupFrame = m_frame.value();

	double factorX = static_cast<double>(frame.width) / groupFrame.width;
	double factorY = static_cast<double>(frame.height) / groupFrame.height;

	for (const auto& shape : m_shapes)
	{
		FrameRect shapeFrame = shape->GetFrame().value();

		float newX = frame.topLeft.x + (shapeFrame.topLeft.x - groupFrame.topLeft.x) * factorX;
		float newY = frame.topLeft.y + (shapeFrame.topLeft.y - groupFrame.topLeft.y) * factorY;
		float newWidth = shapeFrame.width * factorX;
		float newHeight = shapeFrame.height * factorY;

		shape->SetFrame({ { newX, newY }, newWidth, newHeight});
	}

	m_frame = frame;
}

std::optional<FrameRect> ShapeGroup::GetFrame() const
{
	return m_frame;
}

std::shared_ptr<ILineStyle> ShapeGroup::GetOutlineStyle()
{
	throw std::exception();
}

std::shared_ptr<const ILineStyle> ShapeGroup::GetOutlineStyle() const
{
	throw std::exception();
}

std::shared_ptr<IStyle> ShapeGroup::GetFillStyle()
{
	throw std::exception();
}

std::shared_ptr<const IStyle> ShapeGroup::GetFillStyle() const
{
	throw std::exception();
}

std::shared_ptr<IShapeGroup> ShapeGroup::GetShapeGroup()
{
	throw std::exception();
}

std::shared_ptr<const IShapeGroup> ShapeGroup::GetShapeGroup() const
{
	throw std::exception();
}

void ShapeGroup::ReevaluateFrame()
{
	if (m_shapes.empty())
	{
		m_frame = std::nullopt;
		return;
	}

	float minX, minY;
	minX = minY = std::numeric_limits<float>::max();

	float maxX, maxY;
	maxX = maxY = std::numeric_limits<float>::min();

	for (const auto& shape : m_shapes)
	{
		if (!shape->GetFrame().has_value())
		{
			throw std::runtime_error("Cannot evaluate group frame");
		}

		FrameRect frame = shape->GetFrame().value();

		minX = std::min(minX, frame.topLeft.x);
		minY = std::min(minY, frame.topLeft.y);

		maxX = std::max(maxX, frame.topLeft.x + frame.width);
		maxY = std::max(maxY, frame.topLeft.y + frame.height);
	}

	m_frame = FrameRect{
		{ minX, minY },
		maxX - minX,
		maxY - minY
	};
}

void ShapeGroup::AssertIndexWithinRangeExclusive(size_t index) const
{
	if (index > m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
}

void ShapeGroup::AssertIndexWithinRangeInclusive(size_t index) const
{
	if (index >= m_shapes.size())
	{
		throw std::out_of_range("Index is out of range");
	}
}