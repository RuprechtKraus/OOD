#include "State/HasQuarterState.h"

HasQuarterState::HasQuarterState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void HasQuarterState::InsertQuarter()
{
	std::cout << "You can't insert another quarter\n";
}

void HasQuarterState::EjectQuarter()
{
	std::cout << "Quarter returned\n";
	m_gumballMachine.SetNoQuarterState();
}

void HasQuarterState::TurnCrank()
{
	std::cout << "You turned...\n";
	m_gumballMachine.SetSoldState();
}

void HasQuarterState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}

std::string HasQuarterState::ToString() const
{
	return "Waiting for turn of crank";
}