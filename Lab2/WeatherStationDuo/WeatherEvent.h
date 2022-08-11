#pragma once

enum WeatherEvent : unsigned short
{
	TEMPERATURE_CHANGED	   = 0b00001,
	HUMIDITY_CHANGED	   = 0b00010,
	PRESSURE_CHANGED	   = 0b00100,
	WIND_SPEED_CHANGED	   = 0b01000,
	WIND_DIRECTION_CHANGED = 0b10000,
};

constexpr WeatherEvent operator~(WeatherEvent options)
{
	return static_cast<WeatherEvent>(~static_cast<int>(options));
}

constexpr WeatherEvent operator|(WeatherEvent left, WeatherEvent right)
{
	return static_cast<WeatherEvent>(static_cast<int>(left) | static_cast<int>(right));
}

constexpr WeatherEvent operator|=(WeatherEvent& left, WeatherEvent right)
{
	left = left | right;
	return left;
}

constexpr WeatherEvent operator&(WeatherEvent left, WeatherEvent right)
{
	return static_cast<WeatherEvent>(static_cast<int>(left) & static_cast<int>(right));
}

constexpr WeatherEvent operator&=(WeatherEvent& left, WeatherEvent right)
{
	left = left & right;
	return left;
}