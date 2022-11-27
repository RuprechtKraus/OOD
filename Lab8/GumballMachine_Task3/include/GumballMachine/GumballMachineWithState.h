#pragma once
#include "IGumballMachine.h"
#include "State/State.h"
#include <format>
#include <iostream>
#include <memory>

class GumballMachineWithState : private IGumballMachine
{
public:
	GumballMachineWithState(unsigned numBalls);

	void EjectQuarters();
	void InsertQuarter();
	void TurnCrank();
	void Refill(unsigned count);

	std::string ToString() const;

private:
	void ReleaseBall() override;
	void AddBalls(unsigned count) override;
	unsigned GetBallCount() const override;

	bool AddQuarter() override;
	bool ConsumeQuarter() override;
	void ReleaseAllQuarters() override;
	unsigned GetQuarterCount() const override;

	void SetSoldOutState() override;
	void SetNoQuarterState() override;
	void SetSoldState() override;
	void SetHasQuarterState() override;

private:
	static const unsigned MAX_QUARTER_COUNT = 5;
	unsigned m_ballCount = 0;
	unsigned m_quarterCount = 0;
	std::unique_ptr<IState> m_currentState;
};