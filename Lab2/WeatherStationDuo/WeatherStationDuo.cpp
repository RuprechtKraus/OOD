#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"
#include "StatisticsTrackers/WeatherStatistics.h"
#include "WeatherData.h"
#include <iostream>

int main()
{
	WeatherData wd("Outside");
	StatsDisplay dp;
	Display ds;

	wd.RegisterObserver(dp);
	wd.RegisterObserver(ds);

	wd.SetMeasurements(10, 20, 30, 1, 90);
	wd.SetMeasurements(30, 40, 50, 4, 270);
}