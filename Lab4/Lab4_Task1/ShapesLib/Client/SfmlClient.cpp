#include "SfmlClient.h"

SfmlClient::SfmlClient()
	: m_window(sf::RenderWindow(sf::VideoMode(1280, 720), "Shapes", sf::Style::Close))
{
	m_window.clear(sf::Color(255, 255, 255));
	SetCanvas(std::make_unique<SfmlCanvas>(m_window));
}

void SfmlClient::VisualizeDraft(const PictureDraft& draft, Painter& painter)
{
	sf::Event event{};

	painter.DrawPicture(draft, *m_canvas);
	m_window.display();

	while (m_window.isOpen())
	{
		while (m_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window.close();
			}
		}
	}
}