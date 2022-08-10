#include "Displays/Display.h"
//#include "Displays/StatsDisplay.h"
#include "WeatherData.h"
#include <iostream>

int main()
{
	WeatherData wd("Outside", WeatherStationLocation::OUTSIDE);
	//StatsDisplay dp;
	Display ds;

	//wd.RegisterObserver(dp);
	wd.RegisterObserver(ds, TEMPERATURE_CHANGED | HUMIDITY_CHANGED | PRESSURE_CHANGED);

	wd.SetMeasurements(10, 20, 30);
	wd.SetMeasurements(10, 20, 50, 4, 270);
}