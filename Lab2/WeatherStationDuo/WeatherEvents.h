#pragma once

enum WeatherEvents : unsigned short
{
	TEMPERATURE_CHANGED	   = 0b00001,
	HUMIDITY_CHANGED	   = 0b00010,
	PRESSURE_CHANGED	   = 0b00100,
	WIND_SPEED_CHANGED	   = 0b01000,
	WIND_DIRECTION_CHANGED = 0b10000,
};

constexpr WeatherEvents operator~(WeatherEvents options)
{
	return static_cast<WeatherEvents>(~static_cast<int>(options));
}

constexpr WeatherEvents operator|(WeatherEvents left, WeatherEvents right)
{
	return static_cast<WeatherEvents>(static_cast<int>(left) | static_cast<int>(right));
}

constexpr WeatherEvents operator|=(WeatherEvents& left, WeatherEvents right)
{
	left = operator|(left, right);
	return left;
}

constexpr WeatherEvents operator&(WeatherEvents left, WeatherEvents right)
{
	return static_cast<WeatherEvents>(static_cast<int>(left) & static_cast<int>(right));
}

constexpr WeatherEvents operator&=(WeatherEvents& left, WeatherEvents right)
{
	left = operator&(left, right);
	return left;
}