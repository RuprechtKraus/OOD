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

	wd.SetMeasurements(10, 20, 30, 1, 90);
	wd.SetMeasurements(10, 20, 30, 1, 90);
	wd.SetMeasurements(10, 20, 50, 2, 180);
}