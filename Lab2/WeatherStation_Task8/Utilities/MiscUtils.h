#pragma once

constexpr bool IsWithingDeviationRange(
	double value,
	double anchor,
	unsigned absoluteDeviation) noexcept
{
	return value <= anchor + absoluteDeviation && value >= anchor - absoluteDeviation ? true : false;
}