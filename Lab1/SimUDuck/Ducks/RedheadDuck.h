#pragma once
#include "Duck.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck() noexcept;

	void Display() const noexcept override;
};