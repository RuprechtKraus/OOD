#include "WeatherData.h"
#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"

int main()
{
	WeatherData wd;

	Display display;
	wd.RegisterObserver(display);

	StatsDisplay statsDisplay;
	wd.RegisterObserver(statsDisplay);

	wd.SetMeasurements(3, 0.7, 760);
	wd.SetMeasurements(4, 0.8, 761);

	wd.RemoveObserver(statsDisplay);

	wd.SetMeasurements(10, 0.8, 761);
	wd.SetMeasurements(-10, 0.8, 761);
}