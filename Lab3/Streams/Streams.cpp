#include "Application/Application.h"
#include <iostream>

#include "OutputStream/CompressionOutputStream.h"
#include "OutputStream/FileOutputStream.h"
#include "InputStream/DecompressionInputStream.h"
#include "InputStream/FileInputStream.h"

int main(int argc, char* argv[])
try
{
	/*Application app(argc, argv);
	app.Run();*/

	/*std::unique_ptr<IOutputStream> outputStream = std::make_unique<CompressionOutputStream>(
		std::make_unique<FileOutputStream>("compressed.txt"));

	const char* buffer = "I like apples";

	outputStream->WriteBlock(buffer, 13);*/

	std::unique_ptr<IInputStream> inputStream = std::make_unique<DecompressionInputStream>(
		std::make_unique<FileInputStream>("compressed.txt"));

	char* buffer = new char[50];

	int gcount = inputStream->ReadBlock(buffer, 50);
	buffer[gcount] = '\0';

	std::cout << buffer;

	delete[] buffer;
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}