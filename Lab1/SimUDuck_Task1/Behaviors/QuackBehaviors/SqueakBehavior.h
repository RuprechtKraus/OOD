#pragma once
#include "Behaviors/Interfaces/IQuackBehavior.h"

class SqueakBehavior : public IQuackBehavior
{
public:
	void Quack() noexcept override;
};
