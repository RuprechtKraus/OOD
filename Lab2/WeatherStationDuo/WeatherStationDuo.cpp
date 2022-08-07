#include <iostream>
#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"

int main()
{
	WeatherData wd1("Inside");
	WeatherData wd2("Outside");
	StatsDisplay dp;

	wd1.RegisterObserver(dp);
	wd2.RegisterObserver(dp);

	wd1.SetMeasurements(1, 2, 3);
	wd2.SetMeasurements(10, 20, 30);
	wd2.SetMeasurements(20, 30, 40);
}