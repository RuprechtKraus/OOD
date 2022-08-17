#pragma once
#include <string>

enum class StationType
{
	INSIDE,
	OUTSIDE
};

static std::string StationTypeToString(StationType type)
{
	switch (type)
	{
	case StationType::INSIDE:
		return "INSIDE";
	case StationType::OUTSIDE:
		return "OUTSIDE";
	default:
		return "UNKNOWN_TYPE";
	}
}