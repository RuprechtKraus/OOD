#include "GumballMachine/IGumballMachine.h"
#include "State/State.h"
#include "gmock/gmock.h"

using ::testing::Exactly;
using ::testing::Return;
using ::testing::NaggyMock;

class MockGumballMachine : public IGumballMachine
{
public:
	MOCK_METHOD(void, ReleaseBall, (), (override));
	MOCK_METHOD(unsigned, GetBallCount, (), (const, override));

	MOCK_METHOD(void, SetSoldOutState, (), (override));
	MOCK_METHOD(void, SetNoQuarterState, (), (override));
	MOCK_METHOD(void, SetSoldState, (), (override));
	MOCK_METHOD(void, SetHasQuarterState, (), (override));
};

TEST(GumballMachineNoQuarterState, InsertQuarter)
{
	NaggyMock<MockGumballMachine> machine;
	NoQuarterState state(machine);

	EXPECT_CALL(machine, SetHasQuarterState).Times(Exactly(1));

	state.InsertQuarter();
}

TEST(GumballMachineNoQuarterState, EjectQuarter)
{
	NaggyMock<MockGumballMachine> machine;
	NoQuarterState state(machine);

	EXPECT_CALL(machine, SetNoQuarterState).Times(Exactly(0));

	state.EjectQuarter();
}

TEST(GumballMachineNoQuarterState, TurnCrank)
{
	NaggyMock<MockGumballMachine> machine;
	NoQuarterState state(machine);

	EXPECT_CALL(machine, SetSoldState).Times(Exactly(0));

	state.TurnCrank();
}

TEST(GumballMachineNoQuarterState, Dispense)
{
	NaggyMock<MockGumballMachine> machine;
	NoQuarterState state(machine);

	EXPECT_CALL(machine, ReleaseBall).Times(Exactly(0));

	state.Dispense();
}

TEST(GumballMachineHasQuarterState, InsertQuarter)
{
	NaggyMock<MockGumballMachine> machine;
	HasQuarterState state(machine);

	EXPECT_CALL(machine, SetHasQuarterState).Times(Exactly(0));

	state.InsertQuarter();
}

TEST(GumballMachineHasQuarterState, EjectQuarter)
{
	NaggyMock<MockGumballMachine> machine;
	HasQuarterState state(machine);

	EXPECT_CALL(machine, SetNoQuarterState).Times(Exactly(1));

	state.EjectQuarter();
}

TEST(GumballMachineHasQuarterState, TurnCrank)
{
	NaggyMock<MockGumballMachine> machine;
	HasQuarterState state(machine);

	EXPECT_CALL(machine, SetSoldState).Times(Exactly(1));

	state.TurnCrank();
}

TEST(GumballMachineHasQuarterState, Dispense)
{
	NaggyMock<MockGumballMachine> machine;
	HasQuarterState state(machine);

	EXPECT_CALL(machine, ReleaseBall).Times(Exactly(0));

	state.Dispense();
}

TEST(GumballMachineSoldState, InsertQuarter)
{
	NaggyMock<MockGumballMachine> machine;
	SoldState state(machine);

	EXPECT_CALL(machine, SetHasQuarterState).Times(Exactly(0));

	state.InsertQuarter();
}

TEST(GumballMachineSoldState, EjectQuarter)
{
	NaggyMock<MockGumballMachine> machine;
	SoldState state(machine);

	EXPECT_CALL(machine, SetNoQuarterState).Times(Exactly(0));

	state.EjectQuarter();
}

TEST(GumballMachineSoldState, TurnCrank)
{
	NaggyMock<MockGumballMachine> machine;
	SoldState state(machine);

	EXPECT_CALL(machine, SetSoldState).Times(Exactly(0));

	state.TurnCrank();
}

TEST(GumballMachineSoldState, DispenseWithSeveralGumballs)
{
	NaggyMock<MockGumballMachine> machine;
	SoldState state(machine);

	EXPECT_CALL(machine, GetBallCount).WillOnce(Return(3));
	EXPECT_CALL(machine, ReleaseBall).Times(Exactly(1));
	EXPECT_CALL(machine, SetNoQuarterState).Times(Exactly(1));

	state.Dispense();
}

TEST(GumballMachineSoldState, DispenseWithOneGumball)
{
	NaggyMock<MockGumballMachine> machine;
	SoldState state(machine);

	EXPECT_CALL(machine, GetBallCount).WillOnce(Return(0));
	EXPECT_CALL(machine, ReleaseBall).Times(Exactly(1));
	EXPECT_CALL(machine, SetSoldOutState).Times(Exactly(1));

	state.Dispense();
}

TEST(GumballMachineSoldOutState, InsertQuarter)
{
	NaggyMock<MockGumballMachine> machine;
	SoldOutState state(machine);

	EXPECT_CALL(machine, SetHasQuarterState).Times(Exactly(0));

	state.InsertQuarter();
}

TEST(GumballMachineSoldOutState, EjectQuarter)
{
	NaggyMock<MockGumballMachine> machine;
	SoldOutState state(machine);

	EXPECT_CALL(machine, SetNoQuarterState).Times(Exactly(0));

	state.EjectQuarter();
}

TEST(GumballMachineSoldOutState, TurnCrank)
{
	NaggyMock<MockGumballMachine> machine;
	SoldOutState state(machine);

	EXPECT_CALL(machine, SetSoldState).Times(Exactly(0));

	state.TurnCrank();
}

TEST(GumballMachineSoldOutState, Dispense)
{
	NaggyMock<MockGumballMachine> machine;
	SoldOutState state(machine);

	EXPECT_CALL(machine, SetSoldOutState).Times(Exactly(0));

	state.Dispense();
}