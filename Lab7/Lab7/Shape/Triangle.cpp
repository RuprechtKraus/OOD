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

void Triangle::SetFrame(const FrameRect& frame) noexcept
{
	auto oldFrame = m_frame;
	double scaleFactorX = frame.width / m_frame.width;
	double scaleFactorY = frame.height / m_frame.height;
	m_frame = frame;
	AdjustShape(oldFrame, scaleFactorX, scaleFactorY);
}

void Triangle::DrawImpl(ICanvas& canvas) const
{
	canvas.DrawPolygon({ m_vertex1, m_vertex2, m_vertex3 });
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