#pragma once
#include "Behaviors/Interfaces/IFlyBehavior.h"

class FlyWithWingsBehavior : public IFlyBehavior
{
public:
	void Fly() override;

private:
	int m_flyCount{};
};
