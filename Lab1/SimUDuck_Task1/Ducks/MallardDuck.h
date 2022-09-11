#pragma once
#include "Duck.h"

class MallardDuck : public Duck
{
public:
	MallardDuck();

	void Display() const noexcept override;
};
