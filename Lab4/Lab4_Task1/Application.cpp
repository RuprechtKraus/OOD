#include "Application.h"
#include "Canvas/SfmlCanvas.h"
#include "Canvas/StreamCanvas.h"
#include "Designer/Designer.h"
#include "Shapes/ShapeFactory.h"
#include <fstream>
#include <iostream>

Application::Application(const std::string& inputFilename)
	: m_inputFilename(inputFilename)
{
}

void Application::Run()
{
	std::ifstream file(m_inputFilename);

	if (!file.is_open())
	{
		std::cerr << "Cannot open file" << std::endl;
		throw std::runtime_error("Cannot open file");
	}

	ShapeFactory factory;
	Designer designer(factory);
	PictureDraft draft = designer.CreateDraft(file);

	char key{};

	while (true)
	{
		std::cout << "1. Use StreamCanvas\n"
				  << "2. Use SfmlCanvas\n"
				  << "> ";

		key = std::cin.get();

		switch (key)
		{
		case '1':
			VisualizeDraftUsingStreamCanvas(draft);
			break;
		case '2':
			VisualizeDraftUsingSfmlCanvas(draft);
			break;
		default:
			continue;
		}

		break;
	}
}

void Application::VisualizeDraftUsingStreamCanvas(
	const PictureDraft& draft)
{
	StreamCanvas canvas;
	Painter painter;
	painter.DrawPicture(draft, canvas);
}

void Application::VisualizeDraftUsingSfmlCanvas(
	const PictureDraft& draft)
{
	sf::RenderWindow window(sf::VideoMode(1280, 720), "Shapes", sf::Style::Close);
	sf::Event event{};
	SfmlCanvas canvas(window);
	Painter painter;

	window.clear(sf::Color(255, 255, 255));
	painter.DrawPicture(draft, canvas);
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