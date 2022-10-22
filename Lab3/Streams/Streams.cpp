#include "Application/Application.h"
#include <iostream>

int main(int argc, char* argv[])
try
{
	Application app(argc, argv);
	app.Run();
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}