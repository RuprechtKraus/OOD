#pragma once
#include <algorithm>
#include <ranges>
#include <string>

namespace StringUtils
{

inline std::string ToLower(const std::string& str)
{
	std::string result;
	std::ranges::transform(str, std::back_inserter(result), [](char c) { return std::tolower(c); });
	return result;
}

} // namespace StringUtils