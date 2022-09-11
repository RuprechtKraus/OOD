#pragma once
#include "Behaviors/Interfaces/IQuackBehavior.h"

class MuteQuackBehavior : public IQuackBehavior
{
public:
	void Quack() noexcept override;
};