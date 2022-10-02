#pragma once
#include "ICompressor.h"

class RLECompressor : public ICompressor
{
public:
	size_t Compress(char* dst, const char* src, std::streamsize srcSize) const override;
	size_t Decompress(char* dst, const char* src, std::streamsize srcSize) const override;

private:
	std::string GetSymbolOccurrenceInfo(char symbol, size_t count) const;
	char GetNextSymbol(const char* src, size_t& index) const;
	size_t GetSymbolOccurenceCount(const char* src, size_t& index) const;
	std::string UnpackSymbol(size_t& index, char symbol, size_t count) const;
};
