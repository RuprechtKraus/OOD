#pragma once
#include "Behaviors/Interfaces/IDanceBehavior.h"

class WaltzDanceBehavior : public IDanceBehavior
{
public:
	void Dance() noexcept override;
};
