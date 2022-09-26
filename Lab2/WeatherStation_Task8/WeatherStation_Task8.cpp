#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"
#include "WeatherData.h"
#include "WeatherStationType.h"

int main()
{
	OutsideWeatherData wdOut;
	InsideWeatherData wdIn;

	Display display;
	display.AddDataSource(wdIn);
	display.AddDataSource(wdOut);

	StatsDisplay statsDisplay;
	statsDisplay.AddDataSource(wdOut, 5);

	wdIn.SetMeasurements(10, 20, 30);
	wdOut.SetMeasurements(10, 20, 30, 1, 90);
	wdOut.SetMeasurements(10, 20, 50, 2, 180);
}