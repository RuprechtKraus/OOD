#include "RLECompressor.h"
#include <string>
#include <format>

size_t RLECompressor::Compress(char* dst, const char* src, std::streamsize srcSize) const
{
	char symbol{ src[0] };
	size_t count{ 1 };
	std::string result;

	for (size_t i = 1; i <= srcSize; i++)
	{
		if (symbol == src[i])
		{
			count++;
		}
		else
		{
			result += GetSymbolOccurrenceInfo(symbol, count);
			symbol = src[i];
			count = 1;
		}
	}

	memcpy(dst, result.c_str(), result.size());

	return result.size();
}

std::string RLECompressor::GetSymbolOccurrenceInfo(char symbol, size_t count) const
{
	std::string result = "";
	std::string s{ std::to_string(count) };
	result += ("{" + std::format("{},{}", symbol, s) + "}");

	return result;
}

size_t RLECompressor::Decompress(char* dst, const char* src, std::streamsize srcSize) const
{
	size_t count{};
	char symbol{};
	std::string result;

	for (size_t j{}, i = 0; i < srcSize - 1; i++)
	{
		symbol = GetNextSymbol(src, i);
		count = GetSymbolOccurenceCount(src, i);
		result += UnpackSymbol(j, symbol, count);
		count = 0;
	}

	memcpy(dst, result.c_str(), result.size());

	return result.size();
}

char RLECompressor::GetNextSymbol(const char* src, size_t& index) const
{
	char symbol{};

	if (src[index++] == '{')
	{
		symbol = src[index++];
		index++; // Пропускаем запятую
	}

	return symbol;
}

size_t RLECompressor::GetSymbolOccurenceCount(const char* src, size_t& index) const
{
	std::string count;

	while (src[index] != '}')
	{
		count += src[index++];
	}

	return std::stoi(count);
}

std::string RLECompressor::UnpackSymbol(size_t& index, char symbol, size_t count) const
{
	std::string result;
	result.reserve(count);

	for (int i = 0; i < count; i++)
	{
		index++;
		result.push_back(symbol);
	}

	return result;
}