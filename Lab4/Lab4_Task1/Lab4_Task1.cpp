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

	Client client(std::make_unique<StreamCanvas>());
	ShapeFactory factory;
	Designer designer(factory);
	Painter painter;

	client.OrderPainting(file, designer, painter);
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}