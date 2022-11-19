#include "ConsoleCanvas.h"
#include <format>
#include <iostream>

void ConsoleCanvas::SetLineColor(std::optional<RGBAColor> color) noexcept
{
	m_lineColor = color;
}

void ConsoleCanvas::SetFillColor(std::optional<RGBAColor> color) noexcept
{
	m_fillColor = color;
}

void ConsoleCanvas::SetLineWidth(std::optional<int> width) noexcept
{
	m_lineWidth = width;
}

void ConsoleCanvas::DrawLine(const Point& from, const Point& to) const
{
	std::string lineColor = ColorToHexString(m_lineColor);
	int lineWidth = m_lineWidth.value_or(1);

	std::cout << std::format(R"(<line fromX="{}" fromY="{}" toX="{}" toY="{}" color="{}" width="{}">)",
		from.x, from.y, to.x, to.y, lineColor, lineWidth)
			  << std::endl;
}

void ConsoleCanvas::DrawPolygon(const std::vector<Point>& points) const
{
	size_t pointCount = points.size();
	std::string fillColor = ColorToHexString(m_fillColor);

	std::cout << std::format(R"(<polygon fill="{}">)", fillColor) << std::endl;
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
	std::string outlineColor = ColorToHexString(m_lineColor);
	std::string fillColor = ColorToHexString(m_fillColor);
	int lineWidth = m_lineWidth.value_or(1);

	std::cout << std::format(
		R"(<ellipse centerX="{}" centerY="{}" width="{}" height="{}" outline="{}" outlineWidth="{}" fill="{}">)",
		center.x, center.y, width, height, outlineColor, lineWidth, fillColor)
			  << std::endl;
}

std::string ConsoleCanvas::ColorToHexString(std::optional<RGBAColor> color)
{
	return color.has_value() ? std::format("{:#x}", color.value()) : "none";
}