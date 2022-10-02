#include "InputStream/FileInputStream.h"
#include "InputStream/MemoryInputStream.h"
#include "OutputStream/FileOutputStream.h"
#include "OutputStream/MemoryOutputStream.h"
#include <iostream>

int main(int argc, char* argv[])
try
{
	std::vector<uint8_t> buffer{};

	char content[]{ 'A', 'B', 'C', 'D', 'E' };
	MemoryOutputStream outStream(buffer);

	outStream.WriteBlock(content, 5);
	std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<char>(std::cout));
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}