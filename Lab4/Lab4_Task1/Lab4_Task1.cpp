#include "Canvas/SfmlCanvas.h"
#include "Canvas/StreamCanvas.h"
#include "Client/Client.h"
#include "Designer/Designer.h"
#include "Painter/Painter.h"
#include "Shapes/ShapeFactory.h"
#include <fstream>
#include <iostream>

int main()
try
{
	std::ifstream file("input.txt");

	if (!file.is_open())
	{
		std::cerr << "Cannot open file" << std::endl;
		return 1;
	}

	sf::RenderWindow window(sf::VideoMode(1280, 720), "Shapes", sf::Style::Close);
	Client client(std::make_unique<SfmlCanvas>(window));
	sf::Event event{};

	// Client client(std::make_unique<StreamCanvas>());
	ShapeFactory factory;
	Designer designer(factory);
	Painter painter;

	window.clear(sf::Color(255, 255, 255));
	client.OrderPainting(file, designer, painter);
	window.display();

	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
			}
		}
	}
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}