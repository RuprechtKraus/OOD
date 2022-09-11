#include "Duck.h"
#include <assert.h>
#include <iostream>

Duck::Duck(std::unique_ptr<IFlyBehavior>&& flyBehavior, 
	std::unique_ptr<IQuackBehavior>&& quackBehavior,
	std::unique_ptr<IDanceBehavior>&& danceBehavior) noexcept
{
	SetFlyBehavior(std::move(flyBehavior));
	SetQuckBehavior(std::move(quackBehavior));
	SetDanceBehavior(std::move(danceBehavior));
}

void Duck::Fly() const noexcept
{
	m_flyBehavior->Fly();
}

void Duck::Quack() const noexcept
{
	m_quackBehavior->Quack();
}

void Duck::Swim() const noexcept
{
	std::cout << "I'm swimming" << std::endl;
}

void Duck::Dance() const noexcept
{
	m_danceBehavior->Dance();
}

void Duck::SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior) noexcept
{
	assert(flyBehavior);
	m_flyBehavior = std::move(flyBehavior);
}

void Duck::SetQuckBehavior(std::unique_ptr<IQuackBehavior>&& quackBehavior) noexcept
{
	assert(quackBehavior);
	m_quackBehavior = std::move(quackBehavior);
}

void Duck::SetDanceBehavior(std::unique_ptr<IDanceBehavior>&& danceBehavior) noexcept
{
	assert(danceBehavior);
	m_danceBehavior = std::move(danceBehavior);
}