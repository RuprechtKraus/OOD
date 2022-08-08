#include "pch.h"
#include "CppUnitTest.h"
#include "WeatherData.h"
#include "Display.h"

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
	};
}
