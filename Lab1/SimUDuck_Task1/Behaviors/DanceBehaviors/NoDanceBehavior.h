#pragma once
#include "Behaviors/Interfaces/IDanceBehavior.h"

class NoDanceBehavior : public IDanceBehavior
{
public:
	void Dance() noexcept override;
};
