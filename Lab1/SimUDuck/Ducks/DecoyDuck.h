#pragma once
#include "Duck.h"

class DecoyDuck : public Duck
{
public:
	DecoyDuck() noexcept;

	void Display() const noexcept override;
};