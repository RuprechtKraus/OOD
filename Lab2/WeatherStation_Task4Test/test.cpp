#include "pch.h"
#include "MockObservers/MockObserver.h"
#include "WeatherData.h"

TEST(ObserversReceiveUpdatesFromTwoSubjects, HandlesTwoSubjects)
{
	WeatherData wdIn;
	WeatherData wdOut;
	MockObserver observer(wdIn, wdOut);

	wdIn.RegisterObserver(observer);
	wdOut.RegisterObserver(observer);

	wdIn.SetMeasurements(1, 1, 1);
	EXPECT_EQ(observer.GetLastSourceType(), StationType::INSIDE);
	EXPECT_NE(observer.GetLastSourceType(), StationType::OUTSIDE);

	wdOut.SetMeasurements(2, 2, 2);
	EXPECT_EQ(observer.GetLastSourceType(), StationType::OUTSIDE);
	EXPECT_NE(observer.GetLastSourceType(), StationType::INSIDE);
}