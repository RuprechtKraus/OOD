#pragma once
#include "BeverageBase.h"

class Milkshake : public BeverageBase
{
public:
	Milkshake()
		: BeverageBase("Milkshake")
	{
	}

	Milkshake(const std::string& description)
		: BeverageBase(description)
	{
	}

	double GetCost() const noexcept override
	{
		return 80;
	}
};

class SmallMilkshake : public Milkshake
{
public:
	SmallMilkshake()
		: Milkshake("Small Milkshake")
	{
	}

	double GetCost() const noexcept override
	{
		return 50;
	}
};

class MediumMilkshake : public Milkshake
{
public:
	MediumMilkshake()
		: Milkshake("Medium Milkshake")
	{
	}

	double GetCost() const noexcept override
	{
		return 60;
	}
};

class LargeMilkshake : public Milkshake
{
public:
	LargeMilkshake()
		: Milkshake("Large Milkshake")
	{
	}

	double GetCost() const noexcept override
	{
		return 80;
	}
};