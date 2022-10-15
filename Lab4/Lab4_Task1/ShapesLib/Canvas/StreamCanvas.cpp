#include "StreamCanvas.h"
#include <format>

StreamCanvas::StreamCanvas(std::ostream& os)
	: m_stream(os)
	, m_color(Color::Black)
{
}

void StreamCanvas::SetColor(Color color) noexcept
{
	m_color = color;
}

void StreamCanvas::DrawLine(const Point& from, const Point& to)
{
	m_stream
		<< std::format("Drawing {} line from {} {} to {} {}",
			   ColorToString(m_color), from.x, from.y, to.x, to.y)
		<< std::endl;
}

void StreamCanvas::DrawEllipse(const Point& center, int width, int height)
{
	m_stream
		<< std::format("Drawing {} ellipse at {} {} with width {} and height {}",
			   ColorToString(m_color), center.x, center.y, width, height)
		<< std::endl;
}