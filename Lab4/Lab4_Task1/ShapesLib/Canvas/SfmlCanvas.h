#pragma once
#include "ICanvas.h"
#include "SFML/Graphics.hpp"

class SfmlCanvas : public ICanvas
{
public:
	SfmlCanvas(sf::RenderTarget& renderTarget);

	void SetColor(Color color) noexcept override;
	void DrawLine(const Point& from, const Point& to) override;
	void DrawEllipse(const Point& center, int width, int height) override;

private:
	static sf::Color AppColorToSfmlColor(Color color);

	sf::RenderTarget& m_renderTarget;
	Color m_color;
};