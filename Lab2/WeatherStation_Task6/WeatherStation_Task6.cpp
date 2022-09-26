#include "WeatherData.h"
#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"

int main()
{
	OutsideWeatherData wdOut;
	InsideWeatherData wdIn;

	Display display(wdIn, wdOut);
	wdIn.RegisterObserver(display);
	wdOut.RegisterObserver(display);

	/*StatsDisplay statsDisplay;
	wdIn.RegisterObserver(statsDisplay);*/

	wdIn.SetMeasurements(10, 50, 60);
	wdOut.SetMeasurements(10, 20, 30, 1, 90);
	wdOut.SetMeasurements(10, 20, 30, 1, 90);
	wdOut.SetMeasurements(10, 20, 50, 2, 180);
}