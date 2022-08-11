#include "Displays/Display.h"
//#include "Displays/StatsDisplay.h"
#include "WeatherData.h"
#include <iostream>

int main()
{
	WeatherData wd("Outside", StationType::OUTSIDE);
	//StatsDisplay dp;
	Display ds;
	Display ds2;

	//wd.RegisterObserver(dp, WIND_SPEED_CHANGED);
	wd.RegisterObserver(ds, TEMPERATURE_CHANGED | HUMIDITY_CHANGED | PRESSURE_CHANGED);
	wd.UnsubscribeObserverFromEvents(ds, HUMIDITY_CHANGED);
	std::cout << wd.DoesObserverExist(ds) << std::endl;
	//std::cout << wd.DoesObserverExist(ds);
	//wd.RegisterObserver(ds2, PRESSURE_CHANGED);

	wd.SetMeasurements(10, 20, 30);
	wd.SetMeasurements(10, 20, 50, 4, 270);
}