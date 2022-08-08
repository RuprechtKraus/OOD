#include "pch.h"
#include "CppUnitTest.h"
#include "WeatherData.h"
#include "Display.h"
#include "StatsDisplay.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::string_literals;

namespace WeatherStationDuoTest
{
	TEST_CLASS(WeatherStationDuoTest)
	{
	public:
		TEST_METHOD(DisplayReceivesDataFromTwoSubjects)
		{
			std::ostringstream ss;
			WeatherData wdIn("In");
			WeatherData wdOut("Out");
			Display display(ss);

			wdIn.RegisterObserver(display);
			wdOut.RegisterObserver(display);

			wdIn.SetMeasurements(1, 2, 3);
			wdOut.SetMeasurements(4, 5, 6);

			Assert::AreEqual(R"(Source In
Current Temp 1
Current Hum 2
Current Pressure 3
----------------
Source Out
Current Temp 4
Current Hum 5
Current Pressure 6
----------------
)"s, ss.str());
		}

		TEST_METHOD(StatsDisplayReceivesDataFromTwoSubjects)
		{
			std::ostringstream ss;
			WeatherData wdIn("In");
			WeatherData wdOut("Out");
			StatsDisplay display(ss);

			wdIn.RegisterObserver(display);
			wdOut.RegisterObserver(display);

			wdIn.SetMeasurements(1, 2, 3);
			wdOut.SetMeasurements(4, 5, 6);

			Assert::AreEqual(R"(Source In
Max Temp 1
Min Temp 1
Average Temp 1
----------------
Max Hum 2
Min Hum 2
Average Hum 2
----------------
Max Pressure 3
Min Pressure 3
Average Pressure 3
----------------
Source Out
Max Temp 4
Min Temp 4
Average Temp 4
----------------
Max Hum 5
Min Hum 5
Average Hum 5
----------------
Max Pressure 6
Min Pressure 6
Average Pressure 6
----------------
)"s, ss.str());
		}
	};
}
