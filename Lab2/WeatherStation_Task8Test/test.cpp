#include "pch.h"
#include "MockObjects/MockDisplay.h"
#include "WeatherData.h"

TEST(WeatherDataOnSignals, NotifiesObservers)
{
	WeatherData wd;
	MockDisplay display(wd, "");

	wd.SetMeasurements(10, 20, 30);

	EXPECT_TRUE(display.WasUpdated());
}

TEST(WeatherDataOnSignals, NotifiesObserversInOrderOfPriority)
{
	std::vector<std::string> callSequence;
	callSequence.reserve(2);

	WeatherData wd;
	MockDisplay displayOne(wd, "displayOne", &callSequence);
	MockDisplay displayTwo(wd, "displayTwo", &callSequence);

	wd.SetMeasurements(10, 20, 30);

	EXPECT_EQ(callSequence[0], "displayOne");
	EXPECT_EQ(callSequence[1], "displayTwo");
}