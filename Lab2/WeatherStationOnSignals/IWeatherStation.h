#pragma once
#include "WeatherEvent.h"
#include "WeatherStationLocation.h"
#include <boost/signals2.hpp>
#include <limits>
#include <numbers>
#include <string>
#include <variant>
#include <vector>

namespace signals = boost::signals2;

constexpr double NaN = std::numeric_limits<double>::quiet_NaN();

class IWeatherStation;

struct WindInfo
{
	double speed = NaN;
	double direction = NaN;
};

struct WeatherInfo
{
	std::variant<double, WindInfo> value;
	std::string valueName;
	std::string sourceName;
	StationType sourceLocation;
	WeatherEvent event;
};

class IWeatherStation
{
public:
	using Container = std::vector<WeatherInfo>;

private:
	using Signature = void(IWeatherStation*, const Container&);

protected:
	using signal_type = boost::signals2::signal<Signature,
		signals::optional_last_value<boost::function_traits<Signature>::result_type>,
		int,
		std::greater<int>>;

public:
	using slot_type = signal_type::slot_type;

	virtual signals::connection DoOnWeatherDataChange(const slot_type& slot, double priority) = 0;
	virtual Container GetChangedData() const = 0;
};