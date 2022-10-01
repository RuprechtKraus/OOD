#include "InputStream/FileInputStream.h"
#include "OutputStream/FileOutputStream.h"
#include <iostream>

int main(int argc, char* argv[])
try
{
	//FileInputStream inStream("input.txt");
	//FileOutputStream outStream("output.txt");
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}