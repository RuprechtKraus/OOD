#include "pch.h"
#include "CppUnitTest.h"
#include "WeatherData.h"
#include "TestClasses.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace WeatherTest
{
	TEST_CLASS(WeatherTest)
	{
	public:
		
		TEST_METHOD(NotifyObserversDoesNotThrowIfObserverUnsubsDuringNotifying)
		{
			TestObservable subject;
			UnsibscribeObserver unsubObserver(subject);
			UsualObserver usualObserver;

			subject.RegisterObserver(unsubObserver);
			subject.RegisterObserver(usualObserver);

			subject.NotifyObservers();
		}
	};
}
