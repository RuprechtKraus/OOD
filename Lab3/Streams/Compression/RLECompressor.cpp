#include "RLECompressor.h"
#include <string>

void RLECompressor::Compress(char* dst, const char* src, std::streamsize srcSize)
{
	char symbol{ src[0] };
	size_t count{ 1 };

	for (size_t j = 0, i = 1; i < srcSize; i++)
	{
		if (symbol == src[i])
		{
			count++;
		}
		else
		{
			WriteSymbolOccurrenceInfo(dst, j, symbol, count);
			symbol = src[i];
			count = 1;
		}
	}
}

void RLECompressor::WriteSymbolOccurrenceInfo(char* dst, size_t& index, char symbol, size_t count)
{
	dst[index++] = '{';
	dst[index++] = symbol;
	dst[index++] = ',';

	std::string s{ std::to_string(count) };

	memcpy(dst + index, s.c_str(), s.size());
	index += s.size();

	dst[index++] = '}';
}

void RLECompressor::Decompress(char* dst, const char* src, std::streamsize srcSize)
{
	size_t count{};
	char symbol{};

	for (size_t j{}, i = 0; i < srcSize - 1; i++)
	{
		symbol = GetNextSymbol(src, i);
		count = GetSymbolOccurenceCount(src, i);
		UnpackSymbol(dst, j, symbol, count);
		count = 0;
	}
}

char RLECompressor::GetNextSymbol(const char* src, size_t& index)
{
	char symbol{};

	if (src[index++] == '{')
	{
		symbol = src[index++];
		index++; // Пропускаем запятую
	}

	return symbol;
}

size_t RLECompressor::GetSymbolOccurenceCount(const char* src, size_t& index)
{
	std::string count;

	while (src[index] != '}')
	{
		count += src[index++];
	}

	return std::stoi(count);
}

void RLECompressor::UnpackSymbol(char* dst, size_t& index, char symbol, size_t count)
{
	for (int i = 0; i < count; i++)
	{
		dst[index++] = symbol;
	}
}