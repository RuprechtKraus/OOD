#pragma once
#include "Duck.h"

class MallardDuck : public Duck
{
public:
	MallardDuck() noexcept;

	void Display() const noexcept override;
};