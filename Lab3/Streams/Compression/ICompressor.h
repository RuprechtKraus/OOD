#pragma once
#include <ios>

class ICompressor
{
public:
	virtual size_t Compress(char* dst, const char* src, std::streamsize srcSize) const = 0;
	virtual size_t Decompress(char* dst, const char* src, std::streamsize srcSize) const = 0;
	virtual ~ICompressor() = default;
};