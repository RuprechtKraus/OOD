#include <functional>
#include <iostream>
#include <memory>
#include <vector>

using FlyBehavior = std::function<void()>;
using QuackBehavior = std::function<void()>;

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

class Duck
{
public:
	Duck(FlyBehavior flyBehavior, QuackBehavior quackBehavior)
		: m_flyBehavior(std::move(flyBehavior))
		, m_quackBehavior(std::move(quackBehavior))
	{
	}

	void Quack() const
	{
		m_quackBehavior();
	}

	void Swim()
	{
		std::cout << "I'm swimming" << std::endl;
	}

	void Fly()
	{
		m_flyBehavior();
	}

	virtual void Dance()
	{
		std::cout << "I'm Dancing" << std::endl;
	}

	void SetFlyBehavior(FlyBehavior flyBehavior)
	{
		m_flyBehavior = move(flyBehavior);
	}

	virtual void Display() const = 0;
	virtual ~Duck() = default;

private:
	FlyBehavior m_flyBehavior;
	QuackBehavior m_quackBehavior;
};

class MallardDuck : public Duck
{
public:
	MallardDuck()
		: Duck(FlyWithWings, NormalQuack)
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
		: Duck(FlyWithWings, NormalQuack)
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
		: Duck(FlyNoWay, MuteQuack)
	{
	}

	void Display() const override
	{
		std::cout << "I'm decoy duck" << std::endl;
	}

	void Dance() override {}
};
class RubberDuck : public Duck
{
public:
	RubberDuck()
		: Duck(FlyNoWay, SqueakQuack)
	{
	}

	void Display() const override
	{
		std::cout << "I'm rubber duck" << std::endl;
	}

	void Dance() override {}
};

class ModelDuck : public Duck
{
public:
	ModelDuck()
		: Duck(FlyNoWay, NormalQuack)
	{
	}

	void Display() const override
	{
		std::cout << "I'm model duck" << std::endl;
	}

	void Dance() override {}
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