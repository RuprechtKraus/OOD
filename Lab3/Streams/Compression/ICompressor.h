#pragma once
#include <ios>

class ICompressor
{
public:
	virtual void Compress(char* dst, const char* src, std::streamsize srcSize) = 0;
	virtual void Decompress(char* dst, const char* src, std::streamsize srcSize) = 0;
	virtual ~ICompressor() = default;
};