#pragma once
#include "Behaviors/DanceBehavior.h"
#include "Behaviors/FlyBehavior.h"
#include "Behaviors/QuackBehavior.h"

class Duck
{
public:
	Duck(FlyBehavior flyBehavior,
		QuackBehavior quackBehavior,
		DanceBehavior danceBehavior) noexcept;

	virtual ~Duck() noexcept = default;

	void Quack() const noexcept;
	void Swim() const noexcept;
	void Fly() noexcept;
	void Dance() const noexcept;
	void SetFlyBehavior(FlyBehavior flyBehavior) noexcept;
	void SetDanceBevahior(DanceBehavior danceBehavior) noexcept;
	virtual void Display() const = 0;

private:
	void DisplayFlightCount() const noexcept;

	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
	int m_flightCount;
};