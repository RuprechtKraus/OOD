#include "pch.h"
#include "CppUnitTest.h"
#include "WeatherData.h"
#include "TestClasses.h"
#include "PriorityObservable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

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

		TEST_METHOD(PriorityObservableChangesObserverPriorityIfRegistredTwice)
		{
			TestPriorityObservable subject;
			UsualObserver o1;
			UsualObserver o2;
			UsualObserver o3;

			subject.RegisterObserver(3, o1);
			subject.RegisterObserver(1, o2);
			subject.RegisterObserver(2, o1);
			subject.RegisterObserver(5, o3);

			Assert::IsTrue(3 == subject.GetObserversCount(), L"Observers count does not match");
		}

		TEST_METHOD(ObserversWithHigherPriorityGetNorifiedFirst)
		{
			std::ostringstream ss;
			TestPriorityObservable subject;
			ObserverWithOutput o1("o1", ss);
			ObserverWithOutput o2("o2", ss);
			ObserverWithOutput o3("o3", ss);

			subject.RegisterObserver(3, o1);
			subject.RegisterObserver(1, o2);
			subject.RegisterObserver(5, o3);

			subject.ChangeData(5);
			Assert::AreEqual("o3 updated data to 5\no1 updated data to 5\no2 updated data to 5\n"s, 
				ss.str(), L"Actual output does not match expected");
		}

		TEST_METHOD(ChangeObserverPriority)
		{
			std::ostringstream ss;
			TestPriorityObservable subject;
			ObserverWithOutput o1("o1", ss);
			ObserverWithOutput o2("o2", ss);

			subject.RegisterObserver(3, o1);
			subject.RegisterObserver(1, o2);
			subject.SetObserverPriority(4, o1);
			subject.SetObserverPriority(5, o2);

			subject.ChangeData(5);
			Assert::AreEqual("o2 updated data to 5\no1 updated data to 5\n"s,
				ss.str(), L"Actual output does not match expected");
		}

		TEST_METHOD(RemovePriorityObserver)
		{
			std::ostringstream ss;
			TestPriorityObservable subject;
			ObserverWithOutput o1("o1", ss);
			ObserverWithOutput o2("o2", ss);
			ObserverWithOutput o3("o3", ss);

			subject.RegisterObserver(3, o1);
			subject.RegisterObserver(1, o2);
			subject.RegisterObserver(5, o3);
			subject.RemoveObserver(o2);

			subject.ChangeData(5);
			Assert::AreEqual("o3 updated data to 5\no1 updated data to 5\n"s,
				ss.str(), L"Actual output does not match expected");
		}
	};
}
