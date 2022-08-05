#include <cassert>
#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using FlyBehavior = std::function<void()>;
using QuackBehavior = std::function<void()>;
using DanceBehavior = std::function<void()>;

void FlyWithWings()
{
	std::cout << "I'm flying with wings!!!" << std::endl;
}

void FlyNoWay()
{
}

void NormalQuack()
{
	std::cout << "Quack Quack!!!" << std::endl;
}

void SqueakQuack()
{
	std::cout << "Squeak!!!" << std::endl;
}

void MuteQuack()
{
}

void DanceWaltz()
{
	std::cout << "I am dancing waltz" << std::endl;
}

void DanceMinuet()
{
	std::cout << "I am dancing minuet" << std::endl;
}

void NoDance()
{
}

class Duck
{
public:
	Duck(FlyBehavior flyBehavior, QuackBehavior quackBehavior, DanceBehavior danceBehavior) noexcept
		: m_flyBehavior(std::move(flyBehavior))
		, m_quackBehavior(std::move(quackBehavior))
		, m_danceBehavior(std::move(danceBehavior))
	{
	}

	void Quack() const
	{
		assert(m_quackBehavior);
		m_quackBehavior();
	}

	void Swim() const
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly() const
	{
		assert(m_flyBehavior);
		m_flyBehavior();
	}

	void Dance() const
	{
		assert(m_danceBehavior);
		m_danceBehavior();
	}

	void SetFlyBehavior(FlyBehavior flyBehavior) noexcept
	{
		m_flyBehavior = std::move(flyBehavior);
	}

	void SetDanceBevahior(DanceBehavior danceBehavior) noexcept
	{
		m_danceBehavior = std::move(danceBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() noexcept = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
	DanceBehavior m_danceBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, NormalQuack, DanceWaltz)
	{
	}

	void Display() const override
	{
		std::cout << "I'm mallard duck" << std::endl;
	}
};

class RedheadDuck : public Duck
{
public:
	RedheadDuck()
		: Duck(FlyWithWings, NormalQuack, DanceMinuet)
	{
	}

	void Display() const override
	{
		std::cout << "I'm redhead duck" << std::endl;
	}
};
class DecoyDuck : public Duck
{
public:
	DecoyDuck()
		: Duck(FlyNoWay, MuteQuack, NoDance)
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueakQuack, NoDance)
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, NormalQuack, NoDance)
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}
};

void DrawDuck(Duck const& duck)
{
	duck.Display();
}

void PlayWithDuck(Duck& duck)
{
	DrawDuck(duck);
	duck.Quack();
	duck.Fly();
	duck.Dance();
	std::cout << std::endl;
}

int main()
{
	MallardDuck mallardDuck;
	PlayWithDuck(mallardDuck);

	RedheadDuck redheadDuck;
	PlayWithDuck(redheadDuck);

	RubberDuck rubberDuck;
	PlayWithDuck(rubberDuck);

	DecoyDuck decoyDuck;
	PlayWithDuck(decoyDuck);

	ModelDuck modelDuck;
	PlayWithDuck(modelDuck);
	modelDuck.SetFlyBehavior(FlyWithWings);
	PlayWithDuck(modelDuck);
}