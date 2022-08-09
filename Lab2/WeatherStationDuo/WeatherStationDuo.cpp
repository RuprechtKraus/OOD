#include "Display.h"
#include "StatsDisplay.h"
#include "WeatherData.h"
#include <iostream>

int main()
{
	WeatherData wd("Outside");
	StatsDisplay dp;

	wd.RegisterObserver(dp);

	wd.SetMeasurements(10, 20, 30, 1, 90);
	wd.SetMeasurements(30, 40, 50, 4, 270);
}