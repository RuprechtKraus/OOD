#include "ValueStatistics.h"
#include "Helpers/CardinalDirectionHelper.h"
#include <format>

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
	m_sinSum += windInfo.speed * sin(DegreesToRadians(windInfo.direction));
	m_cosSum += windInfo.speed * cos(DegreesToRadians(windInfo.direction));
	m_countAcc++;
}

void CardinalDirectionStatistics::Display() const noexcept
{
	m_output << "Average wind direction " << DegreesToCardinalDirection(
		GetAverage()) << '\n' << std::endl;
}

int CardinalDirectionStatistics::GetAverage() const noexcept
{
	double avgSinSum = m_sinSum / m_countAcc;
	double avgCosSum = m_cosSum / m_countAcc;
	return (static_cast<int>(RadiansToDegrees(
		atan2(avgSinSum, avgCosSum))) + 360) % 360;
}
