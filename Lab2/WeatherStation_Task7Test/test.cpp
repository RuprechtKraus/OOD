#include "pch.h"
#include "MockObjects/MockObservable.h"
#include "MockObjects/MockObserver.h"

TEST(ObservableWithEvents, HandlesSubscriptionToOneEvent)
{
	MockObservable observable;
	MockObserver observerOne;
	MockObserver observerTwo;

	observable.RegisterObserver(observerOne, TEST_EVENT_ONE);
	observable.RegisterObserver(observerTwo, TEST_EVENT_TWO);

	observable.ImitateEvent(TEST_EVENT_ONE);
	EXPECT_TRUE(observerOne.WasUpdated());
	EXPECT_FALSE(observerTwo.WasUpdated());

	observerOne.Reset();
	observerTwo.Reset();

	observable.ImitateEvent(TEST_EVENT_TWO);
	EXPECT_FALSE(observerOne.WasUpdated());
	EXPECT_TRUE(observerTwo.WasUpdated());
}

TEST(ObservableWithEvents, HandlesSubscriptionToMultipleEvents)
{
	MockObservable observable;
	MockObserver observer;

	observable.RegisterObserver(observer, TEST_EVENT_ONE | TEST_EVENT_TWO);

	observable.ImitateEvent(TEST_EVENT_ONE);
	EXPECT_TRUE(observer.WasUpdated());

	observer.Reset();

	observable.ImitateEvent(TEST_EVENT_TWO);
	EXPECT_TRUE(observer.WasUpdated());
}

TEST(ObservableWithEvents, HandlesSubscriptionToEventsAfterRegister)
{
	MockObservable observable;
	MockObserver observer;

	observable.RegisterObserver(observer, TEST_EVENT_ONE);

	observable.ImitateEvent(TEST_EVENT_ONE);
	EXPECT_TRUE(observer.WasUpdated());
	observer.Reset();

	observable.ImitateEvent(TEST_EVENT_TWO);
	EXPECT_FALSE(observer.WasUpdated());

	observer.Reset();
	observable.SubscribeObserverToEvents(observer, TEST_EVENT_TWO);

	observable.ImitateEvent(TEST_EVENT_ONE);
	EXPECT_TRUE(observer.WasUpdated());
	observer.Reset();

	observable.ImitateEvent(TEST_EVENT_TWO);
	EXPECT_TRUE(observer.WasUpdated());
}

TEST(ObservableWithEvents, HandlesUnsubscriptionFromEvents)
{
	MockObservable observable;
	MockObserver observer;

	observable.RegisterObserver(observer, TEST_EVENT_ONE | TEST_EVENT_TWO);
	observable.UnsubscribeObserverFromEvents(observer, TEST_EVENT_TWO);

	observable.ImitateEvent(TEST_EVENT_ONE);
	EXPECT_TRUE(observer.WasUpdated());
	observer.Reset();

	observable.ImitateEvent(TEST_EVENT_TWO);
	EXPECT_FALSE(observer.WasUpdated());
}

TEST(ObservableWithEvents, UnsubscribingFromAllEventsRemovesObserver)
{
	MockObservable observable;
	MockObserver observer;

	observable.RegisterObserver(observer, TEST_EVENT_ONE | TEST_EVENT_TWO);
	observable.UnsubscribeObserverFromEvents(observer, TEST_EVENT_ONE | TEST_EVENT_TWO);

	EXPECT_FALSE(observable.DoesObserverExist(observer));
}