#pragma once
#include "IBeverage.h"

class BeverageBase : public IBeverage
{
public:
	BeverageBase(const std::string& description)
		: m_description(description)
	{
	}

	std::string GetDescription() const noexcept final
	{
		return m_description;
	}

private:
	std::string m_description;
};