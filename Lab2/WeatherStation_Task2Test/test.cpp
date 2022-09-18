#include "pch.h"
#include "Displays/Display.h"
#include "MockObservers/MockObservable.h"
#include "MockObservers/MockObserver.h"
#include "WeatherData.h"

TEST(ObserverRemovingTest, HandlesObserverRemovingItself)
{
	MockObservable observable;
	MockObserver observerOne(observable);
	MockObserver observerTwo(observable);
	MockObserver observerThree(observable);

	observable.RegisterObserver(observerOne);
	observable.RegisterObserver(observerTwo);
	observable.RegisterObserver(observerThree);
	observable.SetValue(5);

	EXPECT_EQ(observerOne.GetValue(), 5);
	EXPECT_EQ(observerTwo.GetValue(), 5);
	EXPECT_EQ(observerThree.GetValue(), 5);
}