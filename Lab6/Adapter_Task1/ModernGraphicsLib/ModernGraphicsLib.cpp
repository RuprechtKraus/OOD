#include "ModernGraphicsLib.h"
#include <format>

namespace modern_graphics_lib
{
ModernGraphicsRenderer::ModernGraphicsRenderer(std::ostream& strm)
	: m_out(strm)
{
}

ModernGraphicsRenderer::~ModernGraphicsRenderer()
{
	if (m_drawing) // «авершаем рисование, если оно было начато
	{
		EndDraw();
	}
}

void ModernGraphicsRenderer::BeginDraw()
{
	if (m_drawing)
	{
		throw std::logic_error("Drawing has already begun");
	}
	m_out << "<draw>" << std::endl;
	m_drawing = true;
}

void ModernGraphicsRenderer::DrawLine(const Point& start, const Point& end)
{
	if (!m_drawing)
	{
		throw std::logic_error("DrawLine is allowed between BeginDraw()/EndDraw() only");
	}
	m_out << std::format(
		R"(  <line fromX="{}" fromY="{}" toX="{}" toY="{}"/>)", start.x, start.y, end.x, end.y)
		  << std::endl;
}

void ModernGraphicsRenderer::EndDraw()
{
	if (!m_drawing)
	{
		throw std::logic_error("Drawing has not been started");
	}
	m_out << "</draw>" << std::endl;
	m_drawing = false;
}
} // namespace modern_graphics_lib