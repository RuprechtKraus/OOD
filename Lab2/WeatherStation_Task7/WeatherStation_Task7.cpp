#include "WeatherData.h"
#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"

int main()
{
	WeatherData wd;

	Display display;
	wd.RegisterObserver(display, ALL_WEATHER_EVENTS);

	StatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay, ALL_WEATHER_EVENTS);

	wd.SetMeasurements(10, 20, 30, 1, 90);
	wd.SetMeasurements(10, 20, 30, 1, 90);
	wd.SetMeasurements(10, 20, 50, 2, 180);
}