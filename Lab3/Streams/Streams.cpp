#include "Application/Application.h"
#include <iostream>

#include "Compression/RLECompressor.h"
#include "InputStream/DecompressionInputStream.h"
#include "InputStream/FileInputStream.h"

int main(int argc, char* argv[])
try
{
	/*Application app(argc, argv);
	app.Run();*/

	std::unique_ptr<IInputStream> inputStream = std::make_unique<DecompressionInputStream>(
		std::make_unique<FileInputStream>("input.txt"));

	char* buffer = new char[50];

	int gcount{};
	uint8_t byte{};

	// std::streamsize gcount = inputStream->ReadBlock(buffer, 50);

	while (true)
	{
		byte = inputStream->ReadByte();
		if (inputStream->IsEOF())
		{
			break;
		}
		std::cout << byte;
	}
	std::cout << std::endl;

	buffer[gcount] = '\0';
	std::cout << "buffer: " << buffer << std::endl;
	std::cout << "eof: " << std::boolalpha << inputStream->IsEOF();

	delete[] buffer;
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}