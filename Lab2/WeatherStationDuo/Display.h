#pragma once
#include "IObserver.h"
#include "WeatherInfo.h"

class Display : public IObserver<WeatherInfo>
{
public:
	void Update(const std::string& source, const WeatherInfo& data) noexcept override;
};
