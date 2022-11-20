#pragma once
#include "IShapeGroup.h"
#include <vector>
#include "Shape/ShapeCollection/ShapeCollection.h"

class ShapeGroup : public IShapeGroup
{
public:
	ShapeGroup();

	void Draw(ICanvas& canvas) const;

	size_t GetShapeCount() const override;
	bool IsEmpty() const noexcept override;

	void InsertShape(
		const std::shared_ptr<IShape>& shape,
		std::optional<size_t> position = std::nullopt) override;
	void RemoveShape(size_t position) override;

	std::shared_ptr<IShape> GetShapeAt(size_t position) override;
	std::shared_ptr<const IShape> GetShapeAt(size_t position) const override;

	void SetFrame(const FrameRect& frame) override;
	std::optional<FrameRect> GetFrame() const override;

	std::shared_ptr<ILineStyle> GetOutlineStyle() override;
	std::shared_ptr<const ILineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<IShapeGroup> GetShapeGroup() override;
	std::shared_ptr<const IShapeGroup> GetShapeGroup() const override;

private:
	void ReevaluateFrame();

	std::optional<FrameRect> m_frame = std::nullopt;
	std::shared_ptr<IShapeCollection> m_shapes;
	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};