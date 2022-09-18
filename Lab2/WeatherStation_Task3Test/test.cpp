#include "pch.h"
#include "MockObservers/MockObservable.h"
#include "MockObservers/MockObserver.h"

TEST(ObserverPriorityTest, HandlesObserversWithPriority)
{
	std::vector<std::string> callSequence;
	MockObservable observable;
	MockObserver observerOne("observerOne", &callSequence);
	MockObserver observerTwo("observerTwo", &callSequence);
	MockObserver observerThree("observerThree", &callSequence);

	observable.RegisterObserver(observerOne, 3);
	observable.RegisterObserver(observerTwo);
	observable.RegisterObserver(observerThree, 2);
	observable.SetValue(5);

	ASSERT_EQ(callSequence[0], "observerOne");
	ASSERT_EQ(callSequence[1], "observerThree");
	ASSERT_EQ(callSequence[2], "observerTwo");
}

TEST(ObservableGeneralTest, ThrowsOnRegisteringObserverTwice)
{
	MockObservable observable;
	MockObserver observerOne("observerOne");

	EXPECT_THROW({
		observable.RegisterObserver(observerOne);
		observable.RegisterObserver(observerOne);
	}, std::runtime_error);
}

TEST(ObservableGeneralTest, ThrowsOnRemovingNotRegisteredObserver)
{
	MockObservable observable;
	MockObserver observerOne("observerOne");

	EXPECT_THROW({
		observable.RemoveObserver(observerOne);
	}, std::runtime_error);
}