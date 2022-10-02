#pragma once
#include "ICompressor.h"

class RLECompressor : public ICompressor
{
public:
	void Compress(char* dst, const char* src, std::streamsize srcSize) override;
	void Decompress(char* dst, const char* src, std::streamsize srcSize) override;

private:
	void WriteSymbolOccurrenceInfo(char* dst, size_t& index, char symbol, size_t count);
	char GetNextSymbol(const char* src, size_t& index);
	size_t GetSymbolOccurenceCount(const char* src, size_t& index);
	void UnpackSymbol(char* dst, size_t& index, char symbol, size_t count);
};
