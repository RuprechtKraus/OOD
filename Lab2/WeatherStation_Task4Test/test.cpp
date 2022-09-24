#include "pch.h"
#include "MockObservers/MockObserver.h"
#include "WeatherData.h"
#include "WeatherStationType.h"

TEST(ObserversReceiveUpdatesFromTwoSubjects, HandlesTwoSubjects)
{
	WeatherData wdIn(WeatherStationType::INSIDE);
	WeatherData wdOut(WeatherStationType::OUTSIDE);
	MockObserver observer;

	wdIn.RegisterObserver(observer);
	wdOut.RegisterObserver(observer);

	wdIn.SetMeasurements(1, 1, 1);
	EXPECT_EQ(observer.GetLastSourceType(), WeatherStationType::INSIDE);
	EXPECT_NE(observer.GetLastSourceType(), WeatherStationType::OUTSIDE);

	wdOut.SetMeasurements(2, 2, 2);
	EXPECT_EQ(observer.GetLastSourceType(), WeatherStationType::OUTSIDE);
	EXPECT_NE(observer.GetLastSourceType(), WeatherStationType::INSIDE);
}