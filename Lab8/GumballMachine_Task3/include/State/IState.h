#pragma once
#include <string>

struct IState
{
	virtual void InsertQuarter() = 0;
	virtual void EjectQuarters() = 0;
	virtual void TurnCrank() = 0;
	virtual void Dispense() = 0;
	virtual void Refill(unsigned count) = 0;

	virtual std::string ToString() const = 0;

	virtual ~IState() = default;
};