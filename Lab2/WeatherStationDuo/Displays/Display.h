#pragma once
#include "Observers/IObserver.h"
#include "WeatherInfo.h"
#include "WeatherEvents.h"
#include <iostream>
#include <format>

class Display : public IObserver<WeatherInfo>
{
public:
	Display(std::ostream& output = std::cout);

	void Update(const std::string& source, const WeatherInfo& data) noexcept override;

private:
	template<typename T>
	void DisplayValue(const std::string& valueName, const T value,
		WeatherEvents happendEvents, WeatherEvents requiredEvent);

	std::ostream& m_output;
};
