#include "ShapeGroup.h"
#include "Style/Group/GroupLineStyle.h"
#include "Style/Group/GroupStyle.h"
#include <algorithm>
#include <stdexcept>

// ShapeGroup::ShapeGroup()
//{
//	LineStyleEnumerator lineStyleEnumerator = [this](const LineStyleCallback& callback) {
//		for (size_t i = 0; i < m_shapes->GetShapeCount(); i++)
//		{
//			callback(*m_shapes->GetShapeAt(i)->GetOutlineStyle());
//		}
//	};
//
//	StyleEnumerator fillStyleEnumerator = [this](const StyleCallback& callback) {
//		for (size_t i = 0; i < m_shapes->GetShapeCount(); i++)
//		{
//			callback(*m_shapes->GetShapeAt(i)->GetFillStyle());
//		}
//	};
//
//	m_shapes = std::make_shared<ShapeCollection>();
//	m_outlineStyle = std::make_shared<GroupLineStyle>(std::move(lineStyleEnumerator));
//	m_fillStyle = std::make_shared<GroupStyle>(std::move(fillStyleEnumerator));
// }

std::shared_ptr<ShapeGroup> ShapeGroup::Create()
{
	std::shared_ptr<ShapeGroup> group(new ShapeGroup());

	LineStyleEnumerator lineStyleEnumerator = [group](const LineStyleCallback& callback) {
		for (size_t i = 0; i < group->GetShapeCount(); i++)
		{
			callback(*group->GetShapeAt(i)->GetOutlineStyle());
		}
	};

	StyleEnumerator fillStyleEnumerator = [group](const StyleCallback& callback) {
		for (size_t i = 0; i < group->GetShapeCount(); i++)
		{
			callback(*group->GetShapeAt(i)->GetFillStyle());
		}
	};

	group->m_shapes = std::make_shared<ShapeCollection>();
	group->m_outlineStyle = std::make_shared<GroupLineStyle>(std::move(lineStyleEnumerator));
	group->m_fillStyle = std::make_shared<GroupStyle>(std::move(fillStyleEnumerator));

	return group;
}

void ShapeGroup::Draw(ICanvas& canvas) const
{
	for (size_t i = 0; i < m_shapes->GetShapeCount(); i++)
	{
		m_shapes->GetShapeAt(i)->Draw(canvas);
	}
}

size_t ShapeGroup::GetShapeCount() const
{
	return m_shapes->GetShapeCount();
}

void ShapeGroup::InsertShape(
	const std::shared_ptr<IShape>& shape,
	std::optional<size_t> position)
{
	m_shapes->InsertShape(shape, position);
}

void ShapeGroup::RemoveShape(size_t position)
{
	m_shapes->RemoveShape(position);
}

std::shared_ptr<IShape> ShapeGroup::GetShapeAt(size_t position)
{
	return m_shapes->GetShapeAt(position);
}

std::shared_ptr<const IShape> ShapeGroup::GetShapeAt(size_t position) const
{
	return m_shapes->GetShapeAt(position);
}

void ShapeGroup::SetFrame(const FrameRect& frame)
{
	auto frameOptional = EvaluateFrame();

	if (!frameOptional)
	{
		throw std::logic_error("Cannot set frame of empty group");
	}

	FrameRect groupFrame = frameOptional.value();

	double factorX = static_cast<double>(frame.width) / groupFrame.width;
	double factorY = static_cast<double>(frame.height) / groupFrame.height;

	for (size_t i = 0; i < m_shapes->GetShapeCount(); i++)
	{
		auto shape = m_shapes->GetShapeAt(i);
		FrameRect shapeFrame = shape->GetFrame().value();

		float newX = frame.topLeft.x + (shapeFrame.topLeft.x - groupFrame.topLeft.x) * factorX;
		float newY = frame.topLeft.y + (shapeFrame.topLeft.y - groupFrame.topLeft.y) * factorY;
		float newWidth = shapeFrame.width * factorX;
		float newHeight = shapeFrame.height * factorY;

		shape->SetFrame({ { newX, newY }, newWidth, newHeight });
	}
}

std::optional<FrameRect> ShapeGroup::GetFrame() const
{
	return EvaluateFrame();
}

std::shared_ptr<ILineStyle> ShapeGroup::GetOutlineStyle()
{
	return m_outlineStyle;
}

std::shared_ptr<const ILineStyle> ShapeGroup::GetOutlineStyle() const
{
	return m_outlineStyle;
}

std::shared_ptr<IStyle> ShapeGroup::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IStyle> ShapeGroup::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IShapeGroup> ShapeGroup::GetShapeGroup()
{
	// return std::shared_ptr<IShapeGroup>(this); // Программа будет падать
	return shared_from_this();
}

std::shared_ptr<const IShapeGroup> ShapeGroup::GetShapeGroup() const
{
	// return std::shared_ptr<const IShapeGroup>(this);
	return shared_from_this();
}

std::optional<FrameRect> ShapeGroup::EvaluateFrame() const
{
	if (IsEmpty())
	{
		return std::nullopt;
	}

	float minX, minY;
	minX = minY = std::numeric_limits<float>::max();

	float maxX, maxY;
	maxX = maxY = std::numeric_limits<float>::min();

	for (size_t i = 0; i < m_shapes->GetShapeCount(); i++)
	{
		auto shape = m_shapes->GetShapeAt(i);
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

	return FrameRect{
		{ minX, minY },
		maxX - minX,
		maxY - minY
	};
}