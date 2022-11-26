#include "State/HasQuarterState.h"

HasQuarterState::HasQuarterState(IGumballMachine& gumballMachine)
	: m_gumballMachine(gumballMachine)
{
}

void HasQuarterState::InsertQuarter()
{
	if (m_gumballMachine.AddQuarter())
	{
		std::cout << "You inserted a quarter\n";
	}
	else
	{
		std::cout << "You can't insert another quarter\n";
	}
}

void HasQuarterState::EjectQuarters()
{
	m_gumballMachine.ReleaseAllQuarters();
	std::cout << "Quarters returned\n";
	m_gumballMachine.SetNoQuarterState();
}

void HasQuarterState::TurnCrank()
{
	std::cout << "You turned...\n";
	if (m_gumballMachine.ConsumeQuarter())
	{
		m_gumballMachine.SetSoldState();
	}
	else
	{
		throw std::runtime_error("No quarters in HasQuarterState");
	}
}

void HasQuarterState::Dispense()
{
	std::cout << "No gumball dispensed\n";
}

std::string HasQuarterState::ToString() const
{
	return "Waiting for turn of crank";
}