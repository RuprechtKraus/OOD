#pragma once
#include <memory>
#include "Behaviors/Interfaces/IFlyBehavior.h"
#include "Behaviors/Interfaces/IQuackBehavior.h"
#include <Behaviors/Interfaces/IDanceBehavior.h>

class Duck
{
public:
	Duck(std::unique_ptr<IFlyBehavior>&& flyBehavior, 
		std::unique_ptr<IQuackBehavior>&& quackBehavior,
		std::unique_ptr<IDanceBehavior>&& danceBehavior) noexcept;

	virtual ~Duck() noexcept = default;

	void Fly() const noexcept;
	void Quack() const noexcept;
	void Swim() const noexcept;
	void Dance() const noexcept;
	void SetFlyBehavior(std::unique_ptr<IFlyBehavior>&& flyBehavior) noexcept;
	void SetQuckBehavior(std::unique_ptr<IQuackBehavior>&& quackBehavior) noexcept;
	void SetDanceBehavior(std::unique_ptr<IDanceBehavior>&& danceBehavior) noexcept;
	virtual void Display() const = 0;

private:
	std::unique_ptr<IFlyBehavior> m_flyBehavior;
	std::unique_ptr<IQuackBehavior> m_quackBehavior;
	std::unique_ptr<IDanceBehavior> m_danceBehavior;
};
