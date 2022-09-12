#include "Duck.h"
#include <assert.h>
#include <iostream>
#include "Behaviors/FlyBehavior.h"
#include "Behaviors/QuackBehavior.h"
#include "Behaviors/DanceBehavior.h"

Duck::Duck(const FlyBehavior& flyBehavior, 
	const QuackBehavior& quackBehavior,
	const DanceBehavior& danceBehavior) noexcept
{
	SetFlyBehavior(flyBehavior);
	SetQuckBehavior(quackBehavior);
	SetDanceBehavior(danceBehavior);
}

void Duck::Fly() const noexcept
{
	if (m_flyBehavior)
	{
		m_flyBehavior();
	}
}

void Duck::Quack() const noexcept
{
	if (m_quackBehavior)
	{
		m_quackBehavior();
	}
}

void Duck::Swim() const noexcept
{
	std::cout << "I'm swimming" << std::endl;
}

void Duck::Dance() const noexcept
{
	if (m_danceBehavior)
	{
		m_danceBehavior();
	}
}

void Duck::SetFlyBehavior(const FlyBehavior& flyBehavior) noexcept
{
	m_flyBehavior = flyBehavior;
}

void Duck::SetQuckBehavior(const QuackBehavior& quackBehavior) noexcept
{
	m_quackBehavior = quackBehavior;
}

void Duck::SetDanceBehavior(const DanceBehavior& danceBehavior) noexcept
{
	m_danceBehavior = danceBehavior;
}