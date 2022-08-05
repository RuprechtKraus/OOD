#pragma once
#include "Duck.h"

class RubberDuck : public Duck
{
public:
	RubberDuck() noexcept;

	void Display() const noexcept override;
};