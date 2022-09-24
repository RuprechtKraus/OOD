#include "WeatherData.h"
#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"

int main()
{
	OutsideWeatherData wdOut;
	InsideWeatherData wdIn;

	Display display;
	wdOut.RegisterObserver(display);

	/*StatsDisplay statsDisplay;
	wdIn.RegisterObserver(statsDisplay);*/

	wdOut.SetMeasurements(10, 20, 30, 1, 90);
	wdOut.SetMeasurements(10, 20, 30, 1, 90);
	wdOut.SetMeasurements(10, 20, 50, 2, 180);
}