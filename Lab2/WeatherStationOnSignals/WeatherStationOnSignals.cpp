#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"
#include "WeatherData.h"
#include <iostream>

int main()
{
	WeatherData wd("Outside", StationType::OUTSIDE);
	StatsDisplay dp;
	Display ds;

	dp.AddDataSource(wd, TEMPERATURE_CHANGED | HUMIDITY_CHANGED);

	wd.SetMeasurements(10, 20, 30);
	wd.SetMeasurements(10, 20, 30, 1, 90);
	wd.SetMeasurements(10, 20, 30, 1, 90);
	wd.SetMeasurements(10, 20, 50, 4, 270);
}