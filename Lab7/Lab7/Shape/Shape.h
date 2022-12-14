#pragma once
#include "IShape.h"
#include "Style/LineStyle.h"
#include "Style/Style.h"
#include <memory>

class Shape : public IShape
{
public:
	void Draw(ICanvas& canvas) const override;

	std::optional<FrameRect> GetFrame() const override;

	std::shared_ptr<ILineStyle> GetOutlineStyle() override;
	std::shared_ptr<const ILineStyle> GetOutlineStyle() const override;

	std::shared_ptr<IStyle> GetFillStyle() override;
	std::shared_ptr<const IStyle> GetFillStyle() const override;

	std::shared_ptr<IShapeGroup> GetShapeGroup() override;
	std::shared_ptr<const IShapeGroup> GetShapeGroup() const override;

protected:
	virtual void DrawImpl(ICanvas& canvas) const = 0; // TODO: AdjustSHape перенести сюда и сделать виртуальным, но пустым

	FrameRect m_frame;
	std::shared_ptr<ILineStyle> m_lineStyle = std::make_shared<LineStyle>();
	std::shared_ptr<IStyle> m_fillStyle = std::make_shared<Style>();

private:
	void PrepareCanvas(ICanvas& canvas) const;
};