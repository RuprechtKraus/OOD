#pragma once
#include "Duck.h"

class RubberDuck : public Duck
{
public:
	RubberDuck();

	void Display() const noexcept override;
};
