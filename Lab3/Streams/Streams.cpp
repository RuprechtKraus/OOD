#include "InputStream/FileInputStream.h"
#include <iostream>

int main(int argc, char* argv[])
try
{
	FileInputStream inStream("input.txt");
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}