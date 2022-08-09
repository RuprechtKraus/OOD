#include "ValueStatistics.h"
#include <format>
#include <numbers>

NumericStatistics::NumericStatistics(const std::string& name, std::ostream& output)
	: m_name(name)
	, m_output(output)
{
}

void NumericStatistics::AddEntry(const double& value) noexcept
{
	m_minValue = std::min(m_minValue, value);
	m_maxValue = std::max(m_maxValue, value);
	m_accValue += value;
	++m_countAcc;
}

void NumericStatistics::Display() const noexcept
{
	m_output << std::format("Max {} ", m_name) << m_maxValue << std::endl;
	m_output << std::format("Min {} ", m_name) << m_minValue << std::endl;
	m_output << std::format("Average {} ", m_name) << (m_accValue / m_countAcc) << '\n'
			 << std::endl;
}

CardinalDirectionStatistics::CardinalDirectionStatistics(
	const std::string& name,
	std::ostream& output)
	: m_name(name)
	, m_output(output)
{
}

void CardinalDirectionStatistics::AddEntry(const WindInfo& windInfo) noexcept
{
	double normalizedDegrees = NormalizeDegrees(windInfo.direction);
	m_sinSum += windInfo.speed * sin(normalizedDegrees * std::numbers::pi / 180);
	m_cosSum += windInfo.speed * cos(normalizedDegrees * std::numbers::pi / 180);
	m_countAcc++;
}

void CardinalDirectionStatistics::Display() const noexcept
{
	m_output << "Average wind direction " << DegreesToCardinalDirection(GetAverage()) << '\n'
			 << std::endl;
}

int CardinalDirectionStatistics::GetAverage() const noexcept
{
	double avgSinSum = m_sinSum / m_countAcc;
	double avgCosSum = m_cosSum / m_countAcc;
	return (static_cast<int>(atan2(avgSinSum, avgCosSum) * 180 / std::numbers::pi) + 360) % 360;
}

std::string CardinalDirectionStatistics::DegreesToCardinalDirection(double degrees)
{
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

bool CardinalDirectionStatistics::IsWithingDeviationRange(
	double value,
	double anchor,
	unsigned absoluteDeviation) noexcept
{
	return value <= anchor + absoluteDeviation && value >= anchor - absoluteDeviation ? true : false;
}

double CardinalDirectionStatistics::NormalizeDegrees(double degrees) noexcept
{
	return static_cast<int>(degrees) % 360;
}

double CardinalDirectionStatistics::DegreesToRadians(double degrees) noexcept
{
	return degrees * (std::numbers::pi / 180);
}

double CardinalDirectionStatistics::RadiansToDegrees(double radians) noexcept
{
	return radians * (180 / std::numbers::pi);
}