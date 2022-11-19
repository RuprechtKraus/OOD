#include "Triangle.h"
#include <algorithm>

Triangle::Triangle(const Point& vertex1, const Point& vertex2, const Point& vertex3) noexcept
	: m_vertex1(vertex1)
	, m_vertex2(vertex2)
	, m_vertex3(vertex3)
{
	auto [leftmost, rightmost] = std::minmax({ m_vertex1.x, m_vertex2.x, m_vertex3.x });
	auto [topmost, bottommost] = std::minmax({ m_vertex1.y, m_vertex2.y, m_vertex3.y });

	m_frame.topLeft = { leftmost, topmost };
	m_frame.width = rightmost - leftmost;
	m_frame.height = bottommost - topmost;
}

void Triangle::Draw(ICanvas& canvas) const
{
	PrepareCanvas(canvas);
	canvas.DrawPolygon({ m_vertex1, m_vertex2, m_vertex3 });
}

void Triangle::PrepareCanvas(ICanvas& canvas) const
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

void Triangle::AdjustShape(const FrameRect& oldFrame, double scaleFactorX, double scaleFactorY)
{   
	m_vertex1 = AdjustPoint(m_vertex1, oldFrame, m_frame, scaleFactorX, scaleFactorY);
	m_vertex2 = AdjustPoint(m_vertex2, oldFrame, m_frame, scaleFactorX, scaleFactorY);
	m_vertex3 = AdjustPoint(m_vertex3, oldFrame, m_frame, scaleFactorX, scaleFactorY);
}

Point Triangle::AdjustPoint(
	const Point& point, 
	const FrameRect& oldFrame, 
	const FrameRect& newFrame, 
	double scaleFactorX, 
	double scaleFactorY)
{
	Point result{};
	result.x = newFrame.topLeft.x + (point.x - oldFrame.topLeft.x) * scaleFactorX;
	result.y = newFrame.topLeft.y + (point.y - oldFrame.topLeft.y) * scaleFactorY;

	return result;
}