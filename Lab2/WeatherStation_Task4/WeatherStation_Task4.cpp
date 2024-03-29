﻿#include "WeatherData.h"
#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"

int main()
{
	WeatherData wdIn;
	WeatherData wdOut;

	Display display(wdIn, wdOut);
	StatsDisplay statsDisplay(wdIn, wdOut);

	wdIn.RegisterObserver(display);
	wdOut.RegisterObserver(display);
	wdIn.RegisterObserver(statsDisplay);
	wdOut.RegisterObserver(statsDisplay);

	wdIn.SetMeasurements(3, 0.7, 760);
	wdOut.SetMeasurements(10, 0.8, 761);

	wdIn.SetMeasurements(4, 0.8, 761);
	wdOut.SetMeasurements(-10, 0.8, 760);
}