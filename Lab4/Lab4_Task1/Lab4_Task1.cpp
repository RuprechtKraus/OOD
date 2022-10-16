#include "Application.h"
#include <iostream>

int main()
try
{
	Application app("input.txt");
	app.Run();
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}