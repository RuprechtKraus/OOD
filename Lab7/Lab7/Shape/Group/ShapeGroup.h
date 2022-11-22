#pragma once
#include "IShapeGroup.h"
#include <vector>
#include "Shape/ShapeCollection/ShapeCollection.h"

class ShapeGroup : public IShapeGroup
{
public:
	[[nodiscard]] static std::shared_ptr<ShapeGroup> Create();

	void Draw(ICanvas& canvas) const;

	size_t GetShapeCount() const override;

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
	ShapeGroup() = default;

	std::optional<FrameRect> EvaluateFrame() const;

	std::shared_ptr<IShapeCollection> m_shapes;
	std::shared_ptr<ILineStyle> m_outlineStyle;
	std::shared_ptr<IStyle> m_fillStyle;
};