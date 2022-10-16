#include "Application.h"
#include "Canvas/SfmlCanvas.h"
#include "Canvas/StreamCanvas.h"
#include "Client/SfmlClient.h"
#include "Client/StreamClient.h"
#include "Designer/Designer.h"
#include "Painter/Painter.h"
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
	Painter painter;
	std::unique_ptr<Client> client;

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
			client = std::make_unique<StreamClient>();
			break;
		case '2':
			client = std::make_unique<SfmlClient>();
			break;
		default:
			continue;
		}

		client->OrderPainting(file, designer, painter);
		break;
	}
}