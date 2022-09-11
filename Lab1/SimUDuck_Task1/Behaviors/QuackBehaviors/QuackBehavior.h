#pragma once
#include "Behaviors/Interfaces/IQuackBehavior.h"

class QuackBehavior : public IQuackBehavior
{
public:
	void Quack() noexcept override;
};
