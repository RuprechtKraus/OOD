#pragma once
#include "WeatherStationType.h"
#include "boost/signals2.hpp"

namespace signals = boost::signals2;

template <typename T>
class IWeatherStation
{
private:
	using Signature = void(IWeatherStation*, const T&);

public:
	using signal_type = signals::signal<Signature,
		signals::optional_last_value<typename boost::function_traits<Signature>::result_type>,
		int,
		std::greater<int>>;
	using slot_type = signal_type::slot_type;

	virtual signals::connection DoOnWeatherDataChange(const slot_type& slot, double priority) = 0;
	virtual T GetChangedData() const = 0;
	virtual WeatherStationType GetStationType() const = 0;

	virtual ~IWeatherStation() = default;
};