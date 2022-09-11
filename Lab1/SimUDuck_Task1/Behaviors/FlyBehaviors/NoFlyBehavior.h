#pragma once
#include "Behaviors/Interfaces/IFlyBehavior.h"

class NoFlyBehavior : public IFlyBehavior
{
public:
	void Fly() noexcept override;
};