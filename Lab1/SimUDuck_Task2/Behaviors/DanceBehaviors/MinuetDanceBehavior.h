#pragma once
#include "Behaviors/Interfaces/IDanceBehavior.h"

class MinuetDanceBehavior : public IDanceBehavior
{
public:
	void Dance() noexcept override;
};
