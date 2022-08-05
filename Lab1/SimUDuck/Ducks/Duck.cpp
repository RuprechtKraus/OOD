#include "Duck.h"
#include <format>

Duck::Duck(FlyBehavior flyBehavior, QuackBehavior quackBehavior, DanceBehavior danceBehavior) noexcept
	: m_flyBehavior(std::move(flyBehavior))
	, m_quackBehavior(std::move(quackBehavior))
	, m_danceBehavior(std::move(danceBehavior))
	, m_flightCount(0)
{
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

void Duck::Fly() noexcept
{
	if (m_flyBehavior)
	{
		m_flightCount++;
		DisplayFlightCount();
		m_flyBehavior();
	}
}

void Duck::Dance() const noexcept
{
	if (m_danceBehavior)
	{
		m_danceBehavior();
	}
}

void Duck::SetFlyBehavior(FlyBehavior flyBehavior) noexcept
{
	m_flightCount = 0;
	m_flyBehavior = std::move(flyBehavior);
}

void Duck::SetDanceBevahior(DanceBehavior danceBehavior) noexcept
{
	m_danceBehavior = std::move(danceBehavior);
}

void Duck::DisplayFlightCount() const noexcept
{
	std::cout << std::format("It's my {} flight!", m_flightCount) << std::endl;
}