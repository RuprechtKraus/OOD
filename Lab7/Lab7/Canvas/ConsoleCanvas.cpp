#include "ConsoleCanvas.h"
#include <iostream>
#include <format>

void ConsoleCanvas::SetLineColor(RGBAColor color) noexcept
{
	m_lineColor = color;
}

void ConsoleCanvas::SetFillColor(RGBAColor color) noexcept
{
	m_fillColor = color;
}

void ConsoleCanvas::SetLineWidth(int width) noexcept
{
	m_lineWidth = width;
}

void ConsoleCanvas::DrawLine(const Point& from, const Point& to) const
{
	std::cout << std::format(R"(<line fromX="{}" fromY="{}" toX="{}" toY="{}" color="{:#x}" width="{}">)",
		from.x, from.y, to.x, to.y, m_lineColor, m_lineWidth) << std::endl;
}

void ConsoleCanvas::DrawPolygon(const std::vector<Point>& points) const
{
	size_t pointCount = points.size();

	std::cout << std::format(R"(<polygon fill="{:#x}">)", m_fillColor) << std::endl;
	for (size_t i = 0; i < pointCount - 1; i++)
	{
		std::cout << "  ";
		DrawLine(points[i], points[i + 1]);
	}
	std::cout << "  ";
	DrawLine(points[pointCount - 1], points[0]);
	std::cout << "</polygon>" << std::endl;
}

void ConsoleCanvas::DrawEllipse(const Point& center, int width, int height) const
{
	std::cout << std::format(
		R"(<ellipse centerX="{}" centerY="{}" width="{}" height="{}" outline="{:#x}" outlineWidth="{}" fill="{:#x}">)",
		center.x, center.y, width, height, m_lineColor, m_lineWidth, m_fillColor) << std::endl;
}