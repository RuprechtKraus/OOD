#pragma once
#include "Observers/IObserver.h"
#include "WeatherInfo.h"
#include <iostream>

class Display : public IObserver<WeatherInfo>
{
public:
	Display(std::ostream& output = std::cout);

	void Update(const std::string& source, const WeatherInfo& data) noexcept override;

private:
	std::ostream& m_output;
};
