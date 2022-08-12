#pragma once
#include "Helpers/CardinalDirectionHelper.h"
#include "Observers/IObserver.h"
#include "WeatherEvent.h"
#include "WeatherInfo.h"
#include <iostream>

class Display : public IObserver<WeatherInfo>
{
public:
	Display(std::ostream& output = std::cout);

	void Update(const WeatherInfo& data) override;

private:
	void DisplayValue(const WeatherInfo& data) const;

	std::ostream& m_output;
};
