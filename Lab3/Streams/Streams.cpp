#include "Cryptography/Cryptographer.h"
#include "InputStream/FileInputStream.h"
#include "InputStream/MemoryInputStream.h"
#include "OutputStream/EncryptionOutputStreamDecorator.h"
#include "OutputStream/FileOutputStream.h"
#include "OutputStream/MemoryOutputStream.h"
#include "InputStream/DecryptionInputStreamDecorator.h"
#include <iostream>

int main(int argc, char* argv[])
try
{
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}