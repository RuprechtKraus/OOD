#pragma once
#include "Duck.h"

class ModelDuck : public Duck
{
public:
	ModelDuck() noexcept;

	void Display() const noexcept override;
};