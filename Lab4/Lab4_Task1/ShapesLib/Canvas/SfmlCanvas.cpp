#include "SfmlCanvas.h"
#include <numbers>

SfmlCanvas::SfmlCanvas(sf::RenderTarget& renderTarget)
	: m_renderTarget(renderTarget)
	, m_color(Color::Black)
{
}

void SfmlCanvas::SetColor(Color color) noexcept
{
	m_color = color;
}

void SfmlCanvas::DrawLine(const Point& from, const Point& to)
{
	sf::Color color(AppColorToSfmlColor(m_color));

	sf::Vertex line[2]{
		sf::Vertex(sf::Vector2f(static_cast<float>(from.x), static_cast<float>(from.y)), color),
		sf::Vertex(sf::Vector2f(static_cast<float>(to.x), static_cast<float>(to.y)), color)
	};

	m_renderTarget.draw(line, 2, sf::Lines);
}

void SfmlCanvas::DrawEllipse(const Point& center, int width, int height)
{
	sf::ConvexShape ellipse;

	const double pi = std::numbers::pi;
	const size_t quantity = 70;

	ellipse.setPointCount(quantity);
	ellipse.move(center.x, center.y);
	ellipse.setOutlineThickness(1);
	ellipse.setOutlineColor(AppColorToSfmlColor(m_color));
	ellipse.setFillColor(sf::Color::Transparent);

	for (size_t i = 0; i < quantity; i++)
	{
		float angle = i * 2 * pi / quantity - pi / 2;
		float x = std::cos(angle) * width;
		float y = std::sin(angle) * height;
		ellipse.setPoint(i, sf::Vector2f(x, y));
	}

	m_renderTarget.draw(ellipse);
}

sf::Color SfmlCanvas::AppColorToSfmlColor(Color color)
{
	switch (color)
	{
	case Color::Green:
		return sf::Color::Green;
	case Color::Red:
		return sf::Color::Red;
	case Color::Blue:
		return sf::Color::Blue;
	case Color::Yellow:
		return sf::Color::Yellow;
	case Color::Pink:
		return sf::Color::Magenta;
	case Color::Black:
		return sf::Color::Black;
	default:
		throw std::invalid_argument("Unknown color");
	}
}