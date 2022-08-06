#pragma once
#include "IObserver.h"
#include "WeatherData.h"
#include <iostream>
#include "IObservable.h"

class Display : public IObserver<WeatherInfo>
{
private:
	void Update(const WeatherInfo& data) const noexcept override;
};