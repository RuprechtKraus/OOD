#pragma once
#include <memory>
#include "Behaviors/FlyBehavior.h"
#include "Behaviors/QuackBehavior.h"
#include "Behaviors/DanceBehavior.h"

class Duck
{
public:
	Duck(const FlyBehavior& flyBehavior,
		const QuackBehavior& quackBehavior,
		const DanceBehavior& danceBehavior) noexcept;

	virtual ~Duck() noexcept = default;

	void Fly() const noexcept;
	void Quack() const noexcept;
	void Swim() const noexcept;
	void Dance() const noexcept;
	void SetFlyBehavior(const FlyBehavior& flyBehavior) noexcept;
	void SetQuckBehavior(const QuackBehavior& quackBehavior) noexcept;
	void SetDanceBehavior(const DanceBehavior& danceBehavior) noexcept;
	virtual void Display() const = 0;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};
