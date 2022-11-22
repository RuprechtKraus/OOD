#include "Shape.h"

void Shape::Draw(ICanvas& canvas) const
{
	PrepareCanvas(canvas);
	DrawImpl(canvas);
}

void Shape::PrepareCanvas(ICanvas& canvas) const
{
	auto lineColor = m_lineStyle->IsEnabled().value() ? m_lineStyle->GetColor()
													  : std::optional<RGBAColor>();
	auto lineWidth = m_lineStyle->IsEnabled().value() ? m_lineStyle->GetLineWidth()
													  : std::optional<int>();
	auto fillColor = m_fillStyle->IsEnabled().value() ? m_fillStyle->GetColor()
													  : std::optional<RGBAColor>();

	canvas.SetLineColor(lineColor);
	canvas.SetLineWidth(lineWidth);
	canvas.SetFillColor(fillColor);
}

std::optional<FrameRect> Shape::GetFrame() const
{
	return m_frame;
}

std::shared_ptr<ILineStyle> Shape::GetOutlineStyle()
{
	return m_lineStyle;
}

std::shared_ptr<const ILineStyle> Shape::GetOutlineStyle() const
{
	return m_lineStyle;
}

std::shared_ptr<IStyle> Shape::GetFillStyle()
{
	return m_fillStyle;
}

std::shared_ptr<const IStyle> Shape::GetFillStyle() const
{
	return m_fillStyle;
}

std::shared_ptr<IShapeGroup> Shape::GetShapeGroup()
{
	return nullptr;
}

std::shared_ptr<const IShapeGroup> Shape::GetShapeGroup() const
{
	return nullptr;
}