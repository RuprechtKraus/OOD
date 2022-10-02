#include "Cryptography/Cryptographer.h"
#include "InputStream/FileInputStream.h"
#include "InputStream/MemoryInputStream.h"
#include "OutputStream/EncryptionOutputStreamDecorator.h"
#include "OutputStream/FileOutputStream.h"
#include "OutputStream/MemoryOutputStream.h"
#include "InputStream/DecryptionInputStreamDecorator.h"
#include "Compression/RLECompressor.h"
#include <iostream>

int main(int argc, char* argv[])
try
{
	const char* cstr = "{a,4}{b,3}{c,1}{g,10}";
	char* result = new char[50];
	RLECompressor rle;

	rle.Decompress(result, cstr, 22);

	std::cout << result;

	delete[] result;
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}