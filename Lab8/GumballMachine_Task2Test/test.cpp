#include "GumballMachine/GumballMachineWithState.h"
#include "GumballMachine/IGumballMachine.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Exactly;
using ::testing::NaggyMock;
using ::testing::Return;

class MockGumballMachine : public IGumballMachine
{
public:
	MOCK_METHOD(void, ReleaseBall, (), (override));
	MOCK_METHOD(unsigned, GetBallCount, (), (const, override));

	MOCK_METHOD(bool, AddQuarter, (), (override));
	MOCK_METHOD(bool, ConsumeQuarter, (), (override));
	MOCK_METHOD(void, ReleaseAllQuarters, (), (override));
	MOCK_METHOD(unsigned, GetQuarterCount, (), (const, override));

	MOCK_METHOD(void, SetSoldOutState, (), (override));
	MOCK_METHOD(void, SetNoQuarterState, (), (override));
	MOCK_METHOD(void, SetSoldState, (), (override));
	MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

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
	machine.TurnCrank();

	std::string str = machine.ToString();
	auto it = str.find("0 quarter");

	EXPECT_TRUE(it != std::string::npos);
}