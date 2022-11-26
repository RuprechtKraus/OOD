#pragma once

struct IGumballMachine
{
	virtual void ReleaseBall() = 0;
	virtual unsigned GetBallCount() const = 0;

	virtual bool AddQuarter() = 0;
	virtual bool ConsumeQuarter() = 0;
	virtual void ReleaseAllQuarters() = 0;
	virtual unsigned GetQuarterCount() const = 0;

	virtual void SetSoldOutState() = 0;
	virtual void SetNoQuarterState() = 0;
	virtual void SetSoldState() = 0;
	virtual void SetHasQuarterState() = 0;

	virtual ~IGumballMachine() = default;
};