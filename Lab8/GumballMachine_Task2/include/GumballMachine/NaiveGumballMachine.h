#pragma once
#include <string>

class NaiveGumballMachine
{
public:
	enum class State
	{
		SoldOut, // Жвачка закончилась
		NoQuarter, // Нет монетки
		HasQuarter, // Есть монетка
		Sold, // Монетка выдана
	};

	NaiveGumballMachine(unsigned count);

	void InsertQuarter();
	void EjectQuarters();
	void TurnCrank();

	std::string ToString() const;

private:
	void Dispense();
	static std::string StateToString(State state);

private:
	static const unsigned MAX_QUARTER_COUNT = 5;
	unsigned m_ballCount;
	unsigned m_quarterCount;
	State m_state = State::SoldOut;
};