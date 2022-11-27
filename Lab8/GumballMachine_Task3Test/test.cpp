#include "GumballMachine/GumballMachineWithState.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using ::testing::Exactly;
using ::testing::NaggyMock;
using ::testing::Return;

class MockGumballMachine : public IGumballMachine
{
public:
	MOCK_METHOD(void, ReleaseBall, (), (override));
	MOCK_METHOD(void, AddBalls, (unsigned count));
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

TEST(GumballMachineTest, HandlesRefill)
{
	GumballMachineWithState machine(1);
	machine.Refill(4);

	std::string str = machine.ToString();
	auto it = str.find("5 gumballs");

	EXPECT_TRUE(it != std::string::npos);
}

TEST(GumballMachineTest, RefillDoesntResetQuarters)
{
	GumballMachineWithState machine(1);
	machine.InsertQuarter();
	machine.InsertQuarter();
	machine.Refill(4);

	std::string str = machine.ToString();
	auto it = str.find("2 quarters");

	EXPECT_TRUE(it != std::string::npos);
}

TEST(GumballMachineHasQuarterStateTest, HandlesRefill)
{
	NaggyMock<MockGumballMachine> machine;
	HasQuarterState state(machine);

	EXPECT_CALL(machine, AddBalls).Times(Exactly(1));

	state.Refill(5);
}

TEST(GumballMachineHasQuarterStateTest, RefillingZeroBallsDoesNothing)
{
	NaggyMock<MockGumballMachine> machine;
	HasQuarterState state(machine);

	EXPECT_CALL(machine, AddBalls).Times(Exactly(0));

	state.Refill(0);
}

TEST(GumballMachineNoQuarterStateTest, HandlesRefill)
{
	NaggyMock<MockGumballMachine> machine;
	NoQuarterState state(machine);

	EXPECT_CALL(machine, AddBalls).Times(Exactly(1));

	state.Refill(5);
}

TEST(GumballMachineNoQuarterStateTest, RefillingZeroBallsDoesNothing)
{
	NaggyMock<MockGumballMachine> machine;
	NoQuarterState state(machine);

	EXPECT_CALL(machine, AddBalls).Times(Exactly(0));

	state.Refill(0);
}

TEST(GumballMachineSoldOutStateTest, HandlesRefill)
{
	NaggyMock<MockGumballMachine> machine;
	SoldOutState state(machine);

	EXPECT_CALL(machine, AddBalls).Times(Exactly(1));
	EXPECT_CALL(machine, SetNoQuarterState).Times(Exactly(1));

	state.Refill(5);
}

TEST(GumballMachineSoldOutStateTest, RefillingZeroBallsDoesNothing)
{
	NaggyMock<MockGumballMachine> machine;
	SoldOutState state(machine);

	EXPECT_CALL(machine, AddBalls).Times(Exactly(0));
	EXPECT_CALL(machine, SetNoQuarterState).Times(Exactly(0));

	state.Refill(0);
}

TEST(GumballMachineSoldStateTest, RefillIsNotAllowed)
{
	NaggyMock<MockGumballMachine> machine;
	SoldState state(machine);

	EXPECT_CALL(machine, AddBalls).Times(Exactly(0));

	state.Refill(5);
}