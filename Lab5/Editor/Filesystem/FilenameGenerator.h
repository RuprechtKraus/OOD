#pragma once
#include <chrono>
#include <filesystem>
#include <random>
#include <string>

namespace fs = std::filesystem;

static Path GetRandomFilename(const Path& extension, unsigned length = 10)
{
	static constexpr char AlphaNumeric[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	static constexpr unsigned AlphaNumericSize = sizeof(AlphaNumeric) - 2;

	unsigned s = std::chrono::system_clock::now().time_since_epoch().count();
	Path filename;
	std::mt19937 g(s);
	std::uniform_int_distribution<int> d(0, AlphaNumericSize);

	for (size_t i = 0; i < length; i++)
	{
		filename += AlphaNumeric[d(g)];
	}

	return filename.replace_extension(extension);
}