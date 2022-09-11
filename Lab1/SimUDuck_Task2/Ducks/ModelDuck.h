#pragma once
#include "Duck.h"

class ModelDuck : public Duck
{
public:
	ModelDuck();

	void Display() const noexcept override;
};
