#pragma once
#include "IGumballMachine.h"
#include "State/State.h"
#include <format>
#include <iostream>
#include <memory>

class GumballMachine : private IGumballMachine
{
public:
	GumballMachine(unsigned numBalls);

	void EjectQuarter();
	void InsertQuarter();
	void TurnCrank();

	std::string ToString() const;

private:
	unsigned GetBallCount() const override;
	void ReleaseBall() override;

	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

private:
	unsigned m_count = 0;
	std::unique_ptr<IState> m_currentState;
};