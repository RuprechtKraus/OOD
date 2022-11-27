#include "GumballMachine/GumballMachineWithState.h"
#include "GumballMachine/NaiveGumballMachine.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

#pragma region GumballMachineWithState

TEST(GumballMachineWithStateTest, CanInsertSeveralQuarters)
{
	GumballMachineWithState machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();

	std::string str = machine.ToString();
	auto it = str.find("2 quarters");

	EXPECT_TRUE(it != std::string::npos);
}

TEST(GumballMachineWithStateTest, CannotInsertMoreThanFiveQuarters)
{
	GumballMachineWithState machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();

	std::string str = machine.ToString();
	auto it = str.find("5 quarters");

	EXPECT_TRUE(it != std::string::npos);
}

TEST(GumballMachineWithStateTest, TurningCrunkWithTwoQuartersReducesThemByOne)
{
	GumballMachineWithState machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();

	std::string str = machine.ToString();
	auto it = str.find("1 quarter");

	EXPECT_TRUE(it != std::string::npos);
}

TEST(GumballMachineWithStateTest, TurningCrunkWithTwoQuartersAndLastBallReturnsRemainingQuarters)
{
	GumballMachineWithState machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();

	std::string str = machine.ToString();
	auto it = str.find("2 quarter");

	EXPECT_TRUE(it != std::string::npos);

	machine.TurnCrank();
	str = machine.ToString();
	it = str.find("0 quarter");

	EXPECT_TRUE(it != std::string::npos);
}

#pragma endregion

#pragma region NaiveGumballMachine

TEST(NaiveGumballMachineTest, CanInsertSeveralQuarters)
{
	NaiveGumballMachine machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();

	std::string str = machine.ToString();
	auto it = str.find("2 quarters");

	EXPECT_TRUE(it != std::string::npos);
}

TEST(NaiveGumballMachineTest, CannotInsertMoreThanFiveQuarters)
{
	NaiveGumballMachine machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.InsertQuarter();

	std::string str = machine.ToString();
	auto it = str.find("5 quarters");

	EXPECT_TRUE(it != std::string::npos);
}

TEST(NaiveGumballMachineTest, TurningCrunkWithTwoQuartersReducesThemByOne)
{
	NaiveGumballMachine machine(5);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.TurnCrank();

	std::string str = machine.ToString();
	auto it = str.find("1 quarter");

	EXPECT_TRUE(it != std::string::npos);
}

TEST(NaiveGumballMachineTest, TurningCrunkWithTwoQuartersAndLastBallReturnsRemainingQuarters)
{
	NaiveGumballMachine machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();

	std::string str = machine.ToString();
	auto it = str.find("2 quarter");

	EXPECT_TRUE(it != std::string::npos);

	machine.TurnCrank();
	str = machine.ToString();
	it = str.find("0 quarter");

	EXPECT_TRUE(it != std::string::npos);
}

#pragma endregion