#pragma once
#include "MiscUtils.h"
#include <numbers>
#include <string>

static std::string DegreesToCardinalDirection(double degrees);
constexpr double NormalizeDegrees(double degrees) noexcept;
constexpr double DegreesToRadians(double degrees) noexcept;
constexpr double RadiansToDegrees(double radians) noexcept;

static std::string DegreesToCardinalDirection(double degrees)
{
	degrees = NormalizeDegrees(degrees);

	if (IsWithingDeviationRange(degrees, 0, 10))
	{
		return "East";
	}

	if (IsWithingDeviationRange(degrees, 90, 10))
	{
		return "North";
	}

	if (IsWithingDeviationRange(degrees, 180, 10))
	{
		return "West";
	}

	if (IsWithingDeviationRange(degrees, 270, 10))
	{
		return "South";
	}

	if (IsWithingDeviationRange(degrees, 45, 35))
	{
		return "North-East";
	}

	if (IsWithingDeviationRange(degrees, 135, 35))
	{
		return "North-West";
	}

	if (IsWithingDeviationRange(degrees, 225, 35))
	{
		return "South-West";
	}

	if (IsWithingDeviationRange(degrees, 315, 35))
	{
		return "South-East";
	}

	return "None";
}

constexpr double NormalizeDegrees(double degrees) noexcept
{
	return static_cast<int>(degrees) % 360;
}

constexpr double DegreesToRadians(double degrees) noexcept
{
	return degrees * (std::numbers::pi / 180);
}

constexpr double RadiansToDegrees(double radians) noexcept
{
	return radians * (180 / std::numbers::pi);
}