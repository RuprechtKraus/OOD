#include "pch.h"
#include "CppUnitTest.h"
#include "WeatherData.h"
#include "Displays/Display.h"
#include "Displays/StatsDisplay.h"
#include "WeatherStationLocation.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

namespace WeatherStationOnSignalsTest
{
	TEST_CLASS(WeatherStationOnSignalsTest)
	{
	public:
		
		TEST_METHOD(DisplayOneEventData)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d(ss);

			d.AddDataSource(wdOut, TEMPERATURE_CHANGED, 0);
			wdOut.SetMeasurements(10, 20, 30);

			Assert::AreEqual(R"(Source Out
Current Temp 10
----------------
)"s, ss.str());
		}

		TEST_METHOD(DisplayTwoEventsData)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d(ss);

			d.AddDataSource(wdOut, TEMPERATURE_CHANGED | WIND_SPEED_CHANGED, 0);
			wdOut.SetMeasurements(10, 20, 30, 5, 180);

			Assert::AreEqual(R"(Source Out
Current Temp 10
----------------
Source Out
Current Wind speed 5
----------------
)"s, ss.str());
		}

		TEST_METHOD(DisplayWindDirectionAsString)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d(ss);

			d.AddDataSource(wdOut, WIND_DIRECTION_CHANGED, 0);
			wdOut.SetMeasurements(10, 20, 30, 5, 180);

			Assert::AreEqual(R"(Source Out
Current Wind direction West
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(DisplayDataFromTwoSubjects)
		{
			std::ostringstream ss;
			WeatherData wdIn("In", StationType::INSIDE);
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d(ss);

			d.AddDataSource(wdIn, TEMPERATURE_CHANGED);
			d.AddDataSource(wdOut, HUMIDITY_CHANGED);
			wdIn.SetMeasurements(10, 20, 30);
			wdOut.SetMeasurements(20, 50, 30);

			Assert::AreEqual(R"(Source In
Current Temp 10
----------------
Source Out
Current Hum 50
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(RegisterObserversWithPriority)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d1(ss);
			Display d2(ss);

			d1.AddDataSource(wdOut, TEMPERATURE_CHANGED, 1);
			d2.AddDataSource(wdOut, HUMIDITY_CHANGED, 2);
			wdOut.SetMeasurements(10, 20, 30);
			wdOut.SetMeasurements(10, 50, 30);

			Assert::AreEqual(R"(Source Out
Current Hum 20
----------------
Source Out
Current Temp 10
----------------
Source Out
Current Hum 50
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(TestRemoveObserver)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d1(ss);
			Display d2(ss);

			d1.AddDataSource(wdOut, TEMPERATURE_CHANGED);
			d2.AddDataSource(wdOut, HUMIDITY_CHANGED);
			wdOut.SetMeasurements(10, 20, 30);
			d1.RemoveDataSource(wdOut);

			Assert::AreEqual(R"(Source Out
Current Temp 10
----------------
Source Out
Current Hum 20
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(TestAddEvent)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d(ss);

			d.AddDataSource(wdOut, TEMPERATURE_CHANGED);
			d.AddEvents(wdOut, HUMIDITY_CHANGED);
			wdOut.SetMeasurements(10, 20, 30);

			Assert::AreEqual(R"(Source Out
Current Temp 10
----------------
Source Out
Current Hum 20
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(TestRemoveEvent)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d(ss);

			d.AddDataSource(wdOut, TEMPERATURE_CHANGED | HUMIDITY_CHANGED);
			d.RemoveEvents(wdOut, HUMIDITY_CHANGED);
			wdOut.SetMeasurements(10, 20, 30);

			Assert::AreEqual(R"(Source Out
Current Temp 10
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(TestSetEvents)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			Display d(ss);

			d.AddDataSource(wdOut, TEMPERATURE_CHANGED | HUMIDITY_CHANGED);
			d.SetEvents(wdOut, WIND_SPEED_CHANGED);
			wdOut.SetMeasurements(10, 20, 30, 5, 90);

			Assert::AreEqual(R"(Source Out
Current Wind speed 5
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(WindInfoDoesntDisplayedFromInsideStationType)
		{
			std::ostringstream ss;
			WeatherData wdIn("In", StationType::INSIDE);
			Display d(ss);

			d.AddDataSource(wdIn, ALL_WEATHER_EVENTS);
			wdIn.SetMeasurements(10, 20, 30, 2, 90);

			Assert::AreEqual(R"(Source In
Current Temp 10
----------------
Source In
Current Hum 20
----------------
Source In
Current Pressure 30
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(StatsDisplayCorrectlyDisplaysNumericStatistic)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			StatsDisplay d(ss);

			d.AddDataSource(wdOut, TEMPERATURE_CHANGED);
			wdOut.SetMeasurements(10, 20, 30);
			wdOut.SetMeasurements(20, 20, 30);
			ss = std::ostringstream();
			wdOut.SetMeasurements(30, 20, 30);

			Assert::AreEqual(R"(Source Out
Max Temp 30
Min Temp 10
Avg Temp 20
----------------
)"s,
				ss.str());
		}

		TEST_METHOD(StatisDisplayCorrectlyDisplaysCardinalDirectionStatistic)
		{
			std::ostringstream ss;
			WeatherData wdOut("Out", StationType::OUTSIDE);
			StatsDisplay d(ss);

			d.AddDataSource(wdOut, WIND_DIRECTION_CHANGED);
			wdOut.SetMeasurements(10, 20, 30, 1, 90);
			wdOut.SetMeasurements(20, 20, 30, 1, 90);
			ss = std::ostringstream();
			wdOut.SetMeasurements(30, 20, 30, 4, 270);

			Assert::AreEqual(R"(Source Out
Average wind direction South
----------------
)"s,
				ss.str());
		}
	};
}
