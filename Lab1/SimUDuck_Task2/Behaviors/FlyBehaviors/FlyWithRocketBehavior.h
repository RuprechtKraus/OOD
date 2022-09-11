#pragma once
#include "Behaviors/Interfaces/IFlyBehavior.h"

class FlyWithRocketBehavior : public IFlyBehavior
{
public:
	void Fly() noexcept override;

private:
	int m_flyCount{};
};
