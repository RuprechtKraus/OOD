#pragma once
#include "Observers/IObserver.h"
#include "WeatherInfo.h"
#include "WeatherEvent.h"
#include <iostream>
#include <format>
#include <unordered_map>

class Display : public IObserver<WeatherInfo>
{
public:
	Display(std::ostream& output = std::cout);

	void Update(const WeatherInfo& data) noexcept override;

private:
	std::ostream& m_output;
};
