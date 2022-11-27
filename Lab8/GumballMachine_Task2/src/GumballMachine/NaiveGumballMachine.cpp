#include "GumballMachine/NaiveGumballMachine.h"
#include <format>
#include <iostream>

NaiveGumballMachine::NaiveGumballMachine(unsigned count)
	: m_ballCount(count)
	, m_quarterCount(0)
	, m_state(count > 0 ? State::NoQuarter : State::SoldOut)
{
}

void NaiveGumballMachine::InsertQuarter()
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You can't insert a quarter, the machine is sold out\n";
		break;
	case State::NoQuarter:
		cout << "You inserted a quarter\n";
		m_quarterCount++;
		m_state = State::HasQuarter;
		break;
	case State::HasQuarter:
		if (m_quarterCount != MAX_QUARTER_COUNT)
		{
			cout << "You inserted a quarter\n";
			m_quarterCount++;
		}
		else
		{
			cout << "You can't insert another quarter\n";	
		}
		break;
	case State::Sold:
		cout << "Please wait, we're already giving you a gumball\n";
		break;
	}
}

void NaiveGumballMachine::EjectQuarters()
{
	using namespace std;
	switch (m_state)
	{
	case State::HasQuarter:
		cout << "Quarters returned\n";
		m_quarterCount = 0;
		m_state = State::NoQuarter;
		break;
	case State::NoQuarter:
		cout << "You haven't inserted a quarter\n";
		break;
	case State::Sold:
		cout << "Sorry you already turned the crank\n";
		break;
	case State::SoldOut:
		cout << "You can't eject, you haven't inserted a quarter yet\n";
		break;
	}
}

void NaiveGumballMachine::TurnCrank()
{
	using namespace std;
	switch (m_state)
	{
	case State::SoldOut:
		cout << "You turned but there's no gumballs\n";
		break;
	case State::NoQuarter:
		cout << "You turned but there's no quarter\n";
		break;
	case State::HasQuarter:
		cout << "You turned...\n";
		if (m_quarterCount > 0)
		{
			m_quarterCount--;
			m_state = State::Sold;
			Dispense();
		}
		else
		{
			throw std::runtime_error("No quarters in HasQuarterState");
		}
		break;
	case State::Sold:
		cout << "Turning twice doesn't get you another gumball\n";
		break;
	}
}

std::string NaiveGumballMachine::ToString() const
{
	auto fmt = std::format(R"(
Mighty Gumball, Inc.
C++-enabled Standing Gumball Model #2016 (with state)
Inventory: {} gumball{} and {} quarter{}
Machine is {}
)",
		m_ballCount, m_ballCount != 1 ? "s" : "",
		m_quarterCount, m_quarterCount != 1 ? "s" : "",
		StateToString(m_state));

	return fmt;
}

void NaiveGumballMachine::Dispense()
{
	using namespace std;
	switch (m_state)
	{
	case State::Sold:
		cout << "A gumball comes rolling out the slot\n";
		--m_ballCount;
		if (m_ballCount == 0)
		{
			cout << "Oops, out of gumballs\n";

			if (m_quarterCount > 0)
			{
				std::cout << "Ejecting quarters\n";
				m_quarterCount = 0;
			}

			m_state = State::SoldOut;
			break;
		}
		else if (m_quarterCount == 0)
		{
			m_state == State::NoQuarter;
			break;
		}
		m_state = State::HasQuarter;
		break;
	case State::NoQuarter:
		cout << "You need to pay first\n";
		break;
	case State::SoldOut:
	case State::HasQuarter:
		cout << "No gumball dispensed\n";
		break;
	}
}

std::string NaiveGumballMachine::StateToString(State state)
{
	switch (state)
	{
	case NaiveGumballMachine::State::SoldOut:
		return "sold out";
	case NaiveGumballMachine::State::NoQuarter:
		return "waiting for quarter";
	case NaiveGumballMachine::State::HasQuarter:
		return "waiting for turn of crank";
	case NaiveGumballMachine::State::Sold:
		return "delivering a gumball";
	default:
		throw std::runtime_error("Unknown state");
	}
}