#include "Compression/RLECompressor.h"
#include "Cryptography/Cryptographer.h"
#include "InputStream/DecompressionInputStream.h"
#include "InputStream/DecryptionInputStream.h"
#include "InputStream/FileInputStream.h"
#include "InputStream/MemoryInputStream.h"
#include "OutputStream/CompressionOutputStream.h"
#include "OutputStream/EncryptionOutputStream.h"
#include "OutputStream/FileOutputStream.h"
#include "OutputStream/MemoryOutputStream.h"
#include <iostream>

template <typename Wrapper, typename... Args>
decltype(auto) WrapStream(const Args&... args)
{
	return [=](auto&& stream) {
		return std::make_unique<Wrapper>(std::forward<decltype(stream)>(stream), args...);
	};
}

template <typename Stream, typename Wrapper>
decltype(auto) operator<<(Stream&& stream, const Wrapper& wrap)
{
	return wrap(std::forward<Stream>(stream));
}

int main(int argc, char* argv[])
try
{
}
catch (const std::exception& e)
{
	std::cerr << e.what() << std::endl;
}