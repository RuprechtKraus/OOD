#pragma once
#include "Duck.h"

class RedheadDuck : public Duck
{
public:
	RedheadDuck();
	
	void Display() const noexcept override;
};
